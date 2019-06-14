#include "CMashRest.h"

mashRest::mashRest()
{

}

mashRest::mashRest(qreal temperature, qreal duration):
    m_temperature(temperature),
    m_duration(duration)
{

}

mashRest::mashRest(const mashRest &other)
{
    m_temperature = other.getTemperature();
    m_duration = other.getDuration();
}

mashRest::~mashRest()
{

}

qreal mashRest::getTemperature() const
{
    return m_temperature;
}

void mashRest::setTemperature(qreal temperature)
{
    m_temperature = temperature;
}

qreal mashRest::getDuration() const
{
    return m_duration;
}

void mashRest::setDuration(qreal duration)
{
    m_duration = duration;
}
