#ifndef CMASHREST_H
#define CMASHREST_H

#include <QtGlobal>

/*!
 * \brief The mashRest class  mashRest giving information about temperature and duration of a rest
 */
class mashRest
{
public:

    mashRest();

    /*!
     * \brief mashRest new rest
     */
    mashRest(qreal temperature, qreal duration);

    mashRest(const mashRest& other);

    virtual ~mashRest();

    /*!
     * \brief getTemperature get rest temperature [°C]
     * \return rest temperature [°C]
     */
    qreal getTemperature() const;
    /*!
     * \brief setTemperature set rest temperature [°C]
     * \param temperature rest temperature [°C]
     */
    void setTemperature(qreal temperature);

    /*!
     * \brief getDuration get rest duration [min]
     * \return rest duration [min]
     */
    qreal getDuration() const;
    /*!
     * \brief setDuration set rest duration [min]
     * \param duration rest duration [min]
     */
    void setDuration(qreal duration);

private:
    /*!
     * \brief m_temperature rest temperature
     */
    qreal m_temperature;
    /*!
     * \brief m_duration rest duration
     */
    qreal m_duration;
};

#endif // CMASHREST_H
