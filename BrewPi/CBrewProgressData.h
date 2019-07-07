#ifndef CBREWPROGRESSDATA_H
#define CBREWPROGRESSDATA_H

#include <QObject>

class BrewProgressData
{
public:
    /*!
     * \brief BrewProgressData standard constructor
     */
    BrewProgressData();

    /*!
     * \brief BrewProgressData extended constructor
     * \param name QString, brew step name
     * \param temperature qreal, brew step temperature
     * \param duration qreal, brew step duration
     */
    BrewProgressData(const QString &name, const qreal &temperature, const qreal &duration);

    /*!
     * \brief name return the name of the brew step
     * \return QString name
     */
    QString name() const;
    /*!
     * \brief setName set the name of the brew step
     * \param name QString
     */
    void setName(const QString &name);

    /*!
     * \brief temperature return the temperature of the brew step
     * \return qreal temperature
     */
    qreal temperature() const;
    /*!
     * \brief setTemperature set the temperature of the brew step
     * \param temperature qreal
     */
    void setTemperature(const qreal &temperature);

    /*!
     * \brief duration return the duration of the brew step
     * \return qreal duration
     */
    qreal duration() const;
    /*!
     * \brief setDuration set the duration of the brew step
     * \param duration qreal
     */
    void setDuration(const qreal &duration);

private:
    /*!
     * \brief m_name contains the name of the brew step
     */
    QString m_name;
    /*!
     * \brief m_temperature contains the temperature of the brew step
     */
    qreal m_temperature;
    /*!
     * \brief m_duration contains the duration of the brew step
     */
    qreal m_duration;
};

#endif // CBREWPROGRESSDATA_H
