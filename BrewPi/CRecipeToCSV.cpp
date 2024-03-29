#include "CRecipeToCSV.h"
#include "CRecipeList.h"
#include "CRecipe.h"
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDebug>

BrewRecipeToCSV::BrewRecipeToCSV()
{
    m_file = new QFile("recipes.txt");
}

BrewRecipeToCSV::~BrewRecipeToCSV()
{
    m_file->close();
    delete m_file;
}

void BrewRecipeToCSV::flush()
{
    m_file->flush();
}

bool BrewRecipeToCSV::recipeListToCSV(BrewRecipeList *list)
{
    if (!m_file->isOpen() && !m_file->open(QIODevice::WriteOnly))
        return false;

    m_file->resize(0);

    qDebug() << list->listEmpty();

    while(!list->listEmpty()) {
        RecipeToCSV(list->takeFirstItem());
    }
    m_file->close();
    return true;
}

void BrewRecipeToCSV::RecipeToCSV(BrewRecipe* recipe)
{
    QTextStream out(m_file);
    out << recipe->getNumber() << ",";
    out << recipe->getName() << ",";
    out << recipe->getDate().toString("dd-MM-yyyy") << ",";
    out << recipe->getAmount() << ",";
    out << recipe->getBrewDura() << ",";
    out << recipe->getStartMashTemp() << ",";
    out << recipe->getStartMashDura() << ",";
    out << recipe->getFerulaTemp() << ",";
    out << recipe->getFerulaDura() << ",";
    out << recipe->getProteaseTemp() << ",";
    out << recipe->getProteaseDura() << ",";
    out << recipe->getMaltoseTemp() << ",";
    out << recipe->getMaltoseDura() << ",";
    out << recipe->getSugarTemp() << ",";
    out << recipe->getSugarDura() << ",";
    out << recipe->getEndTemp() << ",";
    out << recipe->getEndDura() << ",";
    out << endl;
}

QVector<BrewRecipe*>* BrewRecipeToCSV::csvToRecipeList()
{
    QVector<BrewRecipe*> *list = new QVector<BrewRecipe*>;
    qDebug() << m_file->open(QIODevice::ReadOnly);
    if (!m_file->isOpen() && !m_file->open(QIODevice::ReadOnly))
        return nullptr;

    QTextStream in(m_file);
    while(!in.atEnd()) {
        BrewRecipe *recipe = new BrewRecipe();
        QString line = in.readLine();
        recipe = csvToRecipe(line);
        if (recipe != nullptr)
            list->append(recipe);
    }
    qDebug() << "size: " << list->size();
    m_file->close();
    return list;
}

QString BrewRecipeToCSV::getName()
{
    return m_file->fileName();
}

BrewRecipe* BrewRecipeToCSV::csvToRecipe(QString line)
{
    try {
        BrewRecipe *recipe = new BrewRecipe();
        QStringList lineList;
        lineList = line.split(",");
        enum {number, name, date, amount, brewDura,startTemp, startDura,
              ferulaTemp, ferulaDura, proteaseTemp, proteaseDura,
              maltoseTemp, maltoseDura, sugarTemp, sugarDura, endTemp};
        recipe->setNumber(lineList.at(number).toInt());
        recipe->setName(lineList.at(name));
        recipe->setDate(QDate::fromString(lineList.at(date), "dd-MM-yyyy"));
        recipe->setAmount(lineList.at(amount).toDouble());
        recipe->setBrewDura(lineList.at(brewDura).toDouble());
        recipe->setStartMashTemp(lineList.at(startTemp).toDouble());
        recipe->setStartMashDura(lineList.at(startDura).toDouble());
        recipe->setFerulaTemp(lineList.at(ferulaTemp).toDouble());
        recipe->setFerulaDura(lineList.at(ferulaDura).toDouble());
        recipe->setProteaseTemp(lineList.at(proteaseTemp).toDouble());
        recipe->setProteaseDura(lineList.at(proteaseDura).toDouble());
        recipe->setMaltoseTemp(lineList.at(maltoseTemp).toDouble());
        recipe->setMaltoseDura(lineList.at(maltoseDura).toDouble());
        recipe->setSugarTemp(lineList.at(sugarTemp).toDouble());
        recipe->setSugarDura(lineList.at(sugarDura).toDouble());
        recipe->setEndTemp(lineList.at(endTemp).toDouble());
        return recipe;
    } catch (...) {
        return nullptr;
    }
}
