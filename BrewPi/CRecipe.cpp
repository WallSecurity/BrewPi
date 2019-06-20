#include "CRecipe.h"
#include "CMashRest.h"
#include <QDate>
#include "CBrewProgress.h"
#include <qdebug.h>
#include "CGlobals.h"

BrewRecipe::BrewRecipe():
    m_number(0),
    m_name("NAME"),
    m_date(QDate::currentDate()),
    m_Amount(0),
    m_brewDura(0)
{
    m_startMash = new mashRest(0, 0);
    //    m_glucanase = new mashRest(39.0, 15);
    m_ferula = new mashRest(0, 0);
    m_protease = new mashRest(0, 0);
    m_maltose = new mashRest(0, 0);
    m_sugar = new mashRest(0, 0);
    m_end = new mashRest(0, 0);
}

BrewRecipe::BrewRecipe(int number, QString name, QDate date, qreal amount, mashRest start,
                       mashRest ferula, mashRest protease, mashRest maltose, mashRest sugar, mashRest end):
    m_number(number),
    m_name(name),
    m_date(date),
    m_Amount(amount)
{
    m_startMash = new mashRest(start);
    //    m_glucanase = new mashRest(glucanase);
    m_ferula = new mashRest(ferula);
    m_protease = new mashRest(protease);
    m_maltose = new mashRest(maltose);
    m_sugar = new mashRest(sugar);
    m_end = new mashRest(end);
}

BrewRecipe::~BrewRecipe()
{
    delete m_startMash;
    //    delete m_glucanase;
    delete m_ferula;
    delete m_protease;
    delete m_maltose;
    delete m_sugar;
    delete m_end;
}

int BrewRecipe::getNumber() const
{
    return m_number;
}

void BrewRecipe::setNumber(int number)
{
    m_number = number;
}

QString BrewRecipe::getName() const
{
    return m_name;
}

void BrewRecipe::setName(const QString &name)
{
    m_name = name;
}

QString BrewRecipe::printDate() const
{
    return m_date.toString("dd-MM-yyyy");
}

QDate BrewRecipe::getDate() const
{
    return m_date;
}

void BrewRecipe::setDate(const QDate &date)
{
    m_date = date;
}

void BrewRecipe::setpDate(const QString &date)
{
    m_date = QDate::fromString(date, "dd-MM-yyyy");
}

qreal BrewRecipe::getBrewDura() const
{
    return m_brewDura;
}

void BrewRecipe::setBrewDura()
{
    m_brewDura = 0;
    Globals *globals = new Globals();
    BrewProgress *prog = new BrewProgress(*globals);
    prog->setRecipe(QString::number(m_number), m_name,
                    m_date.toString(), QString::number(m_Amount),
                    QString::number(m_startMash->getTemperature()),
                    QString::number(m_startMash->getDuration()),
                    QString::number(m_ferula->getTemperature()),
                    QString::number(m_ferula->getDuration()),
                    QString::number(m_protease->getTemperature()),
                    QString::number(m_protease->getDuration()),
                    QString::number(m_maltose->getTemperature()),
                    QString::number(m_maltose->getDuration()),
                    QString::number(m_sugar->getTemperature()),
                    QString::number(m_sugar->getDuration()),
                    QString::number(m_end->getTemperature()),
                    QString::number(m_end->getDuration()));

    if (!prog->empty()) {
        for (int i = 0; i != prog->size(); i++) {
            m_brewDura += prog->duration(i);
        }
    } else {
        m_brewDura = 0;
    }
    delete prog;
}

void BrewRecipe::setBrewDura(qreal brewDura)
{
    m_brewDura = brewDura;
}

mashRest* BrewRecipe::getStartMash() const
{
    return m_startMash;
}

qreal BrewRecipe::getStartMashTemp() const
{
    return m_startMash->getTemperature();
}

qreal BrewRecipe::getStartMashDura() const
{
    return m_startMash->getDuration();
}

void BrewRecipe::setStartMashTemp(qreal startMashTemp)
{
    m_startMash->setTemperature(startMashTemp);
}

void BrewRecipe::setStartMashDura(qreal startMashDura)
{
    m_startMash->setDuration(startMashDura);
}

//mashRest* BrewRecipe::getGlucanase() const
//{
//    return  m_glucanase;
//}

//qreal BrewRecipe::getGlucanaseTemp() const
//{
//    return m_glucanase->getTemperature();
//}

//int BrewRecipe::getGlucanaseDura() const
//{
//    return m_glucanase->getDuration();
//}

//void BrewRecipe::setGlucanaseTemp(qreal glucanaseTemp)
//{
//    m_glucanase->setTemperature(glucanaseTemp);
//}

//void BrewRecipe::setGlucanaseDura(int glucanaseDura)
//{
//    m_glucanase->setDuration(glucanaseDura);
//}

mashRest* BrewRecipe::getFerula() const
{
    return m_ferula;
}

qreal BrewRecipe::getFerulaTemp() const
{
    return m_ferula->getTemperature();
}

qreal BrewRecipe::getFerulaDura() const
{
    return m_ferula->getDuration();
}

void BrewRecipe::setFerulaTemp(qreal ferulaTemp)
{
    m_ferula->setTemperature(ferulaTemp);
}

void BrewRecipe::setFerulaDura(qreal ferulaDura)
{
    m_ferula->setDuration(ferulaDura);
}

mashRest* BrewRecipe::getProtease() const
{
    return m_protease;
}

qreal BrewRecipe::getProteaseTemp() const
{
    return m_protease->getTemperature();
}

qreal BrewRecipe::getProteaseDura() const
{
    return m_protease->getDuration();
}

void BrewRecipe::setProteaseTemp(qreal proteaseTemp)
{
    m_protease->setTemperature(proteaseTemp);
}

void BrewRecipe::setProteaseDura(qreal proteaseDura)
{
    m_protease->setDuration(proteaseDura);
}

mashRest* BrewRecipe::getMaltose() const
{
    return m_maltose;
}

qreal BrewRecipe::getMaltoseTemp() const
{
    return m_maltose->getTemperature();
}

qreal BrewRecipe::getMaltoseDura() const
{
    return m_maltose->getDuration();
}

void BrewRecipe::setMaltoseTemp(qreal maltoseTemp)
{
    m_maltose->setTemperature(maltoseTemp);
}

void BrewRecipe::setMaltoseDura(qreal maltoseDura)
{
    m_maltose->setDuration(maltoseDura);
}

mashRest* BrewRecipe::getSugar() const
{
    return m_sugar;
}

qreal BrewRecipe::getSugarTemp() const
{
    return m_sugar->getTemperature();
}

qreal BrewRecipe::getSugarDura() const
{
    return m_sugar->getDuration();
}

void BrewRecipe::setSugarTemp(qreal sugarTemp)
{
    m_sugar->setTemperature(sugarTemp);
}

void BrewRecipe::setSugarDura(qreal sugarDura)
{
    m_sugar->setDuration(sugarDura);
}

mashRest *BrewRecipe::getEnd() const
{
    return m_end;
}

qreal BrewRecipe::getEndTemp() const
{
    return m_end->getTemperature();
}

qreal BrewRecipe::getEndDura() const
{
    return 0;
}

void BrewRecipe::setEndTemp(qreal endTemp)
{
    m_end->setTemperature(endTemp);
}

qreal BrewRecipe::getAmount() const
{
    return m_Amount;
}

void BrewRecipe::setAmount(qreal Amount)
{
    m_Amount = Amount;
}
