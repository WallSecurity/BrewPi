#include "CRecipeModel.h"
#include "CRecipeList.h"
#include "CRecipe.h"
#include "CMashRest.h"

BrewRecipeModel::BrewRecipeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_list = new BrewRecipeList();
}

BrewRecipeModel::~BrewRecipeModel()
{
    delete m_list;
}

int BrewRecipeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_list)
        return 0;

    return m_list->getSize();
}

QVariant BrewRecipeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_list)
        return QVariant();

    const BrewRecipe *recipe = m_list->getItemAt(index.row());
    switch (role) {
    case number:
        return QVariant(recipe->getNumber());
    case name:
        return QVariant(recipe->getName());
    case date:
        return QVariant(recipe->printDate());
    case amount:
        return QVariant(recipe->getAmount());
    case brewDura:
        return QVariant(recipe->getBrewDura());
    case startTemp:
        return QVariant(recipe->getStartMashTemp());
    case startDura:
        return QVariant(recipe->getStartMashDura());
    case ferulaTemp:
        return QVariant(recipe->getFerulaTemp());
    case ferulaDura:
        return QVariant(recipe->getFerulaDura());
    case proteaseTemp:
        return QVariant(recipe->getProteaseTemp());
    case proteaseDura:
        return QVariant(recipe->getProteaseDura());
    case maltoseTemp:
        return QVariant(recipe->getMaltoseTemp());
    case maltoseDura:
        return QVariant(recipe->getMaltoseDura());
    case sugarTemp:
        return QVariant(recipe->getSugarTemp());
    case sugarDura:
        return QVariant(recipe->getSugarDura());
    case endTemp:
        return QVariant(recipe->getEndTemp());
    case endDura:
        return QVariant(recipe->getEndDura());
    }
    return QVariant();
}

Qt::ItemFlags BrewRecipeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool BrewRecipeModel::insertRecipe(QString number,
                                   QString name,
                                   QString date,
                                   QString amount,
                                   QString startT,
                                   QString startD,
                                   QString ferulaT,
                                   QString ferulaD,
                                   QString protT,
                                   QString protD,
                                   QString maltT,
                                   QString maltD,
                                   QString sugarT,
                                   QString sugarD,
                                   QString endT,
                                   QString endD)
{
    if (!m_list || QModelIndex().isValid())
        return false;

    QDate nDate = QDate::fromString(date, "dd-MM-yyyy");

    mashRest *startMash = new mashRest(startT.toDouble(), startD.toDouble());
    mashRest *ferula = new mashRest(ferulaT.toDouble(), ferulaD.toDouble());
    mashRest *protease = new mashRest(protT.toDouble(), protD.toDouble());
    mashRest *maltose = new mashRest(maltT.toDouble(), maltD.toDouble());
    mashRest *sugar = new mashRest(sugarT.toDouble(), sugarD.toDouble());
    mashRest *end = new mashRest(endT.toDouble(), endD.toDouble());

    BrewRecipe *recipe = new BrewRecipe(number.toInt(), name, nDate, amount.toDouble(),
                                        *startMash, *ferula, *protease, *maltose, *sugar, *end);

    recipe->setBrewDura();

    beginInsertRows(QModelIndex(), 0, 0);

    if (m_list->insertAt(0, recipe) == true) {
        endInsertRows();
        return true;
    }

    endInsertRows();
    return false;
    }

bool BrewRecipeModel::removeRow(int row)
{
    if (!m_list || row < 0 || QModelIndex().isValid())
        return false;

    bool rem = false;

    beginRemoveRows(QModelIndex(), row, row);

    if (m_list->removeItemAt(row) == true)
        rem = true;

    endRemoveRows();

    return rem;
}

QHash<int, QByteArray> BrewRecipeModel::roleNames() const
{
    QHash<int, QByteArray> hRoles;
    hRoles[number] = "number";
    hRoles[name] = "name";
    hRoles[date] = "date";
    hRoles[amount] = "amount";
    hRoles[brewDura] = "brewDura";
    hRoles[startTemp] = "startTemp";
    hRoles[startDura] = "startDura";
    hRoles[ferulaTemp] = "ferulaTemp";
    hRoles[ferulaDura] = "ferulaDura";
    hRoles[proteaseTemp] = "proteaseTemp";
    hRoles[proteaseDura] = "proteaseDura";
    hRoles[maltoseTemp] = "maltoseTemp";
    hRoles[maltoseDura] = "maltoseDura";
    hRoles[sugarTemp] = "sugarTemp";
    hRoles[sugarDura] = "sugarDura";
    hRoles[endTemp] = "endTemp";
    hRoles[endDura] = "endDura";
    return hRoles;
}

BrewRecipeList *BrewRecipeModel::getList() const
{
    return m_list;
}

void BrewRecipeModel::setList(BrewRecipeList *list)
{
    m_list = list;
}

QVariant BrewRecipeModel::at(int index, int role) const
{
    if (!m_list || index < 0 || index > m_list->getSize())
        return "";

    BrewRecipe *recipe = m_list->getItemAt(index);
    if (recipe == nullptr)
        return "";
    else {
        switch (role) {
        case number:
            return QVariant(recipe->getNumber());
        case name:
            return QVariant(recipe->getName());
        case date:
            return QVariant(recipe->printDate());
        case amount:
            return QVariant(recipe->getAmount());
        case brewDura:
            return QVariant(recipe->getBrewDura());
        case startTemp:
            return QVariant(recipe->getStartMashTemp());
        case startDura:
            return QVariant(recipe->getStartMashDura());
        case ferulaTemp:
            return QVariant(recipe->getFerulaTemp());
        case ferulaDura:
            return QVariant(recipe->getFerulaDura());
        case proteaseTemp:
            return QVariant(recipe->getProteaseTemp());
        case proteaseDura:
            return QVariant(recipe->getProteaseDura());
        case maltoseTemp:
            return QVariant(recipe->getMaltoseTemp());
        case maltoseDura:
            return QVariant(recipe->getMaltoseDura());
        case sugarTemp:
            return QVariant(recipe->getSugarTemp());
        case sugarDura:
            return QVariant(recipe->getSugarDura());
        case endTemp:
            return QVariant(recipe->getEndTemp());
        case endDura:
            return QVariant(recipe->getEndDura());
        }
        return "";
    }
}

bool BrewRecipeModel::setAt(int row,
                            QString number,
                            QString name,
                            QString date,
                            QString amount,
                            QString startT,
                            QString startD,
                            QString ferulaT,
                            QString ferulaD,
                            QString protT,
                            QString protD,
                            QString maltT,
                            QString maltD,
                            QString sugarT,
                            QString sugarD,
                            QString endT,
                            QString endD)
{
    if (!m_list || row < 0 || row > m_list->getSize())
        return false;

    QDate nDate = QDate::fromString(date, "dd-MM-yyyy");

    mashRest *startMash = new mashRest(startT.toDouble(), startD.toDouble());
    mashRest *ferula = new mashRest(ferulaT.toDouble(), ferulaD.toDouble());
    mashRest *protease = new mashRest(protT.toDouble(), protD.toDouble());
    mashRest *maltose = new mashRest(maltT.toDouble(), maltD.toDouble());
    mashRest *sugar = new mashRest(sugarT.toDouble(), sugarD.toDouble());
    mashRest *end = new mashRest(endT.toDouble(), endD.toDouble());
    BrewRecipe *recipe = new BrewRecipe(number.toInt(), name, nDate, amount.toDouble(),
                                        *startMash, *ferula, *protease, *maltose, *sugar, *end);

    recipe->setBrewDura();

    if (m_list->setItemAt(row, *recipe) == true) {
        emit dataChanged(this->index(row), this->index(row));
        return true;
    } else {
        return false;
    }
}
