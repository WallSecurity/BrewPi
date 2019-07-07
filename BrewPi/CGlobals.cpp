#include "CGlobals.h"
#include <QFile>
#include <QTextStream>

Globals::Globals(QObject *parent) :
    QObject(parent),
    m_heatingMultiplierStartFerula(1.0),
    m_heatingMultiplierFerulaProtease(1.0),
    m_heatingMultiplierProteaseMaltose(1.0),
    m_heatingMultiplierMaltoseSugar(1.0),
    m_heatingMultiplierSugarEnd(1.0),
    m_comportNumber(24),
    m_intervallTimer(1.0),
    m_motorspeedHeat(75.0),
    m_motorspeedNormal(50.0)
{
    m_file = new QFile("settings.txt");
    loadSettingsFromFile();
}

Globals::~Globals()
{
    m_file->close();
    delete m_file;
}

bool Globals::saveSettingsToFile()
{
    if (!m_file->isOpen() && !m_file->open(QIODevice::WriteOnly))
        return false;

    m_file->resize(0);

    QTextStream out(m_file);

    out << m_heatingMultiplierStartFerula << ",";
    out << m_heatingMultiplierFerulaProtease << ",";
    out << m_heatingMultiplierProteaseMaltose << ",";
    out << m_heatingMultiplierMaltoseSugar << ",";
    out << m_heatingMultiplierSugarEnd << ",";
    out << m_comportNumber << ",";
    out << m_intervallTimer << ",";
    out << m_motorspeedHeat << ",";
    out << m_motorspeedNormal << ",";

    m_file->close();
    return true;
}

bool Globals::loadSettingsFromFile()
{
    if (!m_file->isOpen() && !m_file->open(QIODevice::ReadOnly))
        return false;

    QTextStream in(m_file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        try {
            QStringList lineList;
            lineList = line.split(",");
            enum {heatingMultiplierStartFerula, heatingMultiplierFerulaProtease,
                 heatingMultiplierProteaseMaltose, heatingMultiplierMaltoseSugar,
                 heatingMultiplierSugarEnd, comportNumber, intervallTimer,
                 motorspeedHeat, motorspeedNormal};
            m_heatingMultiplierStartFerula = lineList.at(heatingMultiplierStartFerula).toDouble();
            m_heatingMultiplierFerulaProtease = lineList.at(heatingMultiplierFerulaProtease).toDouble();
            m_heatingMultiplierProteaseMaltose = lineList.at(heatingMultiplierProteaseMaltose).toDouble();
            m_heatingMultiplierMaltoseSugar = lineList.at(heatingMultiplierMaltoseSugar).toDouble();
            m_heatingMultiplierSugarEnd = lineList.at(heatingMultiplierSugarEnd).toDouble();
            m_comportNumber = lineList.at(comportNumber).toInt();
            m_intervallTimer = lineList.at(intervallTimer).toInt();
            m_motorspeedHeat = lineList.at(motorspeedHeat).toDouble();
            m_motorspeedNormal = lineList.at(motorspeedNormal).toDouble();
        } catch (...) {
            m_file->close();
            return false;
        }
    }

    m_file->close();
    return true;
}

qreal Globals::heatingMultiplierStartFerula() const
{
    return m_heatingMultiplierStartFerula;
}

void Globals::setHeatingMultiplierStartFerula(const qreal &heatingMultiplierStartFerula)
{
    m_heatingMultiplierStartFerula = heatingMultiplierStartFerula;
}

qreal Globals::heatingMultiplierFerulaProtease() const
{
    return m_heatingMultiplierFerulaProtease;
}

void Globals::setHeatingMultiplierFerulaProtease(const qreal &heatingMultiplierFerulaProtease)
{
    m_heatingMultiplierFerulaProtease = heatingMultiplierFerulaProtease;
}

qreal Globals::heatingMultiplierProteaseMaltose() const
{
    return m_heatingMultiplierProteaseMaltose;
}

void Globals::setHeatingMultiplierProteaseMaltose(const qreal &heatingMultiplierProteaseMaltose)
{
    m_heatingMultiplierProteaseMaltose = heatingMultiplierProteaseMaltose;
}

qreal Globals::heatingMultiplierMaltoseSugar() const
{
    return m_heatingMultiplierMaltoseSugar;
}

void Globals::setHeatingMultiplierMaltoseSugar(const qreal &heatingMultiplierMaltoseSugar)
{
    m_heatingMultiplierMaltoseSugar = heatingMultiplierMaltoseSugar;
}

qreal Globals::heatingMultiplierSugarEnd() const
{
    return m_heatingMultiplierSugarEnd;
}

void Globals::setHeatingMultiplierSugarEnd(const qreal &heatingMultiplierSugarEnd)
{
    m_heatingMultiplierSugarEnd = heatingMultiplierSugarEnd;
}

int Globals::comportNumber() const
{
    return m_comportNumber;
}

void Globals::setComportNumber(int comportNumber)
{
    m_comportNumber = comportNumber;
}

int Globals::intervallTimer() const
{
    return m_intervallTimer;
}

void Globals::setIntervallTimer(int intervallTimer)
{
    m_intervallTimer = intervallTimer;
}

qreal Globals::motorspeedHeat() const
{
    return m_motorspeedHeat;
}

void Globals::setMotorspeedHeat(const qreal &motorspeedHeat)
{
    m_motorspeedHeat = motorspeedHeat;
}

qreal Globals::motorspeedNormal() const
{
    return m_motorspeedNormal;
}

void Globals::setMotorspeedNormal(const qreal &motorspeedNormal)
{
    m_motorspeedNormal = motorspeedNormal;
}
