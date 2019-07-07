#ifndef CTEMPERATUREDATA_H
#define CTEMPERATUREDATA_H

#include <QObject>

class QPointF;
class QTimer;
class Globals;

/*!
 * \brief The BrewTemperatureGraph class creates a simple graph to represent the current temperature
 */
class BrewSensorData: public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)

public:
    BrewSensorData(const Globals &globals, QObject *parent = nullptr);

    virtual ~BrewSensorData();

    /*!
     * \brief getTemperature gets current temperature from arduino
     * \return temperature as string
     */
//    void setTemperature();

    /*!
     * \brief setupTotalTimer setup the total timer to set the end time of the brew process
     * \param length total length as int
     * \return true, if successful
     */
    Q_INVOKABLE bool setupTimers(int length);

    /*!
     * \brief endTimers end total timer
     * \return true, if successful
     */
    Q_INVOKABLE bool endTimers();

    Q_INVOKABLE void setIntervall();

    /*!
     * \brief endTimers end intervall timer
     * \return true, if successful
     */
    Q_INVOKABLE void endIntervall();

    /*!
     * \brief getTimer return time counted so far
     */
    Q_INVOKABLE double getTimer();

    /*!
      * \brief temperature returns current temperature as QString
      */
    Q_INVOKABLE QString temperature();

    /*!
      * \brief dTemperature returns current temperature as double
      */
    Q_INVOKABLE double temperatureToDouble();

    /*!
     * \brief getSpeed return speed of motor driver
     * \return QString
     */
    Q_INVOKABLE QString getSpeed() const;

public slots:
    void startBrewProcess();
    void endBrewProcess();
    void setTemperature();
    void setTemperatureNoConnect();
    void setMotorSpeed(QString speed);
    void setAutoMotorSpeed(QString step);

signals:
    void temperatureChanged();
    void speedChanged();

private:
    /*!
     * \brief m_timer QTimer Object for intervall points
     */
    QTimer *m_intervall;
    /*!
     * \brief m_timer QTimer Object for intervall points without connections
     */
    QTimer *m_intervallNoConnect;
    /*!
     * \brief m_total total timer
     */
    QTimer *m_total;
    /*!
     * \brief m_totalTime holds total time for process
     */
    int m_totalTime;
    /*!
     * \brief m_temperature holds current temperature in °C
     */
    QString m_temperature;
    /*!
      * \brief m_speed
      * */
    QString m_speed;

    /*!
     * \brief m_globals global variables manager
     */
    const Globals *m_globals;
};

#endif // CTEMPERATUREDATA_H
