#include "CBrewProgressData.h"

BrewProgressData::BrewProgressData() :
    m_name(""),
    m_temperature(0),
    m_duration(0)
{

}

BrewProgressData::BrewProgressData(const QString &name, const qreal &temperature, const qreal &duration) :
    m_name(name),
    m_temperature(temperature),
    m_duration(duration)
{

}

QString BrewProgressData::name() const
{
    return m_name;
}

void BrewProgressData::setName(const QString &name)
{
    m_name = name;
}

qreal BrewProgressData::temperature() const
{
    return m_temperature;
}

void BrewProgressData::setTemperature(const qreal &temperature)
{
    m_temperature = temperature;
}

qreal BrewProgressData::duration() const
{
    return m_duration;
}

void BrewProgressData::setDuration(const qreal &duration)
{
    m_duration = duration;
}
