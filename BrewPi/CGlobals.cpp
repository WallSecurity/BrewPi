#include "CGlobals.h"

CGlobals::CGlobals(QObject *parent) : QObject(parent)
{

}

qreal CGlobals::heatingMultiplierStartFerula() const
{
    return m_heatingMultiplierStartFerula;
}

void CGlobals::setHeatingMultiplierStartFerula(const qreal &heatingMultiplierStartFerula)
{
    m_heatingMultiplierStartFerula = heatingMultiplierStartFerula;
}

qreal CGlobals::heatingMultiplierFerulaProtease() const
{
    return m_heatingMultiplierFerulaProtease;
}

void CGlobals::setHeatingMultiplierFerulaProtease(const qreal &heatingMultiplierFerulaProtease)
{
    m_heatingMultiplierFerulaProtease = heatingMultiplierFerulaProtease;
}

qreal CGlobals::heatingMultiplierProteaseMaltose() const
{
    return m_heatingMultiplierProteaseMaltose;
}

void CGlobals::setHeatingMultiplierProteaseMaltose(const qreal &heatingMultiplierProteaseMaltose)
{
    m_heatingMultiplierProteaseMaltose = heatingMultiplierProteaseMaltose;
}

qreal CGlobals::heatingMultiplierMaltoseSugar() const
{
    return m_heatingMultiplierMaltoseSugar;
}

void CGlobals::setHeatingMultiplierMaltoseSugar(const qreal &heatingMultiplierMaltoseSugar)
{
    m_heatingMultiplierMaltoseSugar = heatingMultiplierMaltoseSugar;
}

qreal CGlobals::heatingMultiplierSugarEnd() const
{
    return m_heatingMultiplierSugarEnd;
}

void CGlobals::setHeatingMultiplierSugarEnd(const qreal &heatingMultiplierSugarEnd)
{
    m_heatingMultiplierSugarEnd = heatingMultiplierSugarEnd;
}

int CGlobals::comportNumber() const
{
    return m_comportNumber;
}

void CGlobals::setComportNumber(int comportNumber)
{
    m_comportNumber = comportNumber;
}

int CGlobals::intervallTimer() const
{
    return m_intervallTimer;
}

void CGlobals::setIntervallTimer(int intervallTimer)
{
    m_intervallTimer = intervallTimer;
}

qreal CGlobals::motorspeedHeat() const
{
    return m_motorspeedHeat;
}

void CGlobals::setMotorspeedHeat(const qreal &motorspeedHeat)
{
    m_motorspeedHeat = motorspeedHeat;
}

qreal CGlobals::motorspeedNormal() const
{
    return m_motorspeedNormal;
}

void CGlobals::setMotorspeedNormal(const qreal &motorspeedNormal)
{
    m_motorspeedNormal = motorspeedNormal;
}
