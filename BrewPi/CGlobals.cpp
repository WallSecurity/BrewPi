#include "CGlobals.h"

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
