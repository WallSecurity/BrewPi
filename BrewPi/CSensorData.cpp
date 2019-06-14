#include "CSensorData.h"
#include <QPointF>
#include <QTimer>
#include "rs232.h"
#include "globalsConstants.h"
#include <iostream>
#include <QDebug>

BrewSensorData::BrewSensorData(QObject *parent) :
    QObject (parent),
    m_totalTime(0),
    m_temperature("00.00")
{
    RS232_OpenComport(COMPORT_NUMBER, BAUDRATE, TRANS_MODE);
    m_intervall = new QTimer(this);
    m_total = new QTimer(this);
    Sleep(ARDUINO_SLEEPTIMER);
    connect(m_intervall, SIGNAL(timeout()), this, SLOT(setTemperature()));
    connect(m_total, SIGNAL(timeout()), this, SLOT(endBrewProcess()));
}

BrewSensorData::~BrewSensorData()
{
    delete m_intervall;
    delete m_total;
    RS232_CloseComport(COMPORT_NUMBER);
}

void BrewSensorData::setTemperature()
{
    int n = 0;
    unsigned char buf[6];
    char str[1][5];
    strcpy(str[0], "301\n");
    {
        RS232_cputs(COMPORT_NUMBER, str[0]);

        n = RS232_PollComport(COMPORT_NUMBER, buf, 5);
        if (n>0) {
            m_temperature = QString((char *)buf);
            qDebug() << "m_temp: " <<m_temperature;
            qDebug() << "m_time: " <<getTimer();
            qDebug() << "m_total: " <<m_totalTime;
            qDebug() << "m_remaining: " <<m_total->remainingTime();
            emit temperatureChanged();
        }
    }
}

void BrewSensorData::setMotorSpeed(QString speed)
{
    double realSpeed = speed.toDouble()*2.55;
    m_speed = speed;
    speed = QString::number(realSpeed);
    if (speed.toInt() >= 0 && speed.toInt() <= 255) {
        speed += "\n";
        QByteArray speedArray = speed.toLocal8Bit();
        char str[1][5];
        strcpy(str[0], speedArray.data());
        RS232_cputs(COMPORT_NUMBER, str[0]);
    }
}

void BrewSensorData::setAutoMotorSpeed(QString step)
{
    qDebug() << step;
    double realSpeed;
    QString speed;
    if (step.startsWith("Aufheizen", Qt::CaseInsensitive)) {
        realSpeed = MOTORSPEEDHEAT * 2.55;
        m_speed = QString::number(MOTORSPEEDHEAT);
    } else {
        realSpeed = MOTORSPEEDNORMAL * 2.55;
        m_speed = QString::number(MOTORSPEEDNORMAL);
    }
    speed = QString::number(realSpeed);
    if (speed.toInt() >= 0 && speed.toInt() <= 255) {
        speed += "\n";
        QByteArray speedArray = speed.toLocal8Bit();
        char str[1][5];
        strcpy(str[0], speedArray.data());
        RS232_cputs(COMPORT_NUMBER, str[0]);
    }
}

QString BrewSensorData::getSpeed() const
{
    return m_speed;
}

bool BrewSensorData::setupTimers(int length)
{
    if (length > 0) {
        m_totalTime = length * 60000;
        m_total->setSingleShot(true);
        m_total->start(m_totalTime);
        m_intervall->start(INTERVALL_TIMER * 1000);
        return true;
    } else {
        return false;
    }
}

bool BrewSensorData::endTimers()
{
    if (m_total->isActive() && m_intervall->isActive()) {
        m_total->stop();
        m_intervall->stop();
        return true;
    } else {
        return false;
    }
}

double BrewSensorData::getTimer()
{
    if (m_total->remainingTime() == -1)
        return 0;
    return ((double(m_totalTime) - double(m_total->remainingTime())) / 60000);
}

QString BrewSensorData::temperature()
{
    return m_temperature;
}

double BrewSensorData::temperatureToDouble()
{
    return m_temperature.toDouble();
}

void BrewSensorData::startBrewProcess()
{
    m_total->start(m_totalTime);
}

void BrewSensorData::endBrewProcess()
{
    m_intervall->stop();
    m_total->stop();
}
