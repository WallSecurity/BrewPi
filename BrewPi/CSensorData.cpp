#include "CSensorData.h"
#include <QPointF>
#include <QTimer>
#include "rs232.h"
#include "CGlobals.h"
#include <iostream>
#include <QDebug>

BrewSensorData::BrewSensorData(const Globals &globals, QObject *parent) :
    QObject (parent),
    m_totalTime(0),
    m_temperature("00.00"),
    m_globals(&globals)
{
    char TRANS_MODE[] = {'8', 'N', '1', 0};
    RS232_OpenComport(m_globals->comportNumber(), 9600, TRANS_MODE);
    m_intervall = new QTimer(this);
    m_total = new QTimer(this);
    m_intervallNoConnect = new QTimer(this);
    connect(m_intervall, SIGNAL(timeout()), this, SLOT(setTemperature()));
    connect(m_total, SIGNAL(timeout()), this, SLOT(endBrewProcess()));
    connect(m_intervallNoConnect, SIGNAL(timeout()), this, SLOT(setTemperatureNoConnect()));
}

BrewSensorData::~BrewSensorData()
{
    delete m_intervall;
    delete m_total;
    delete m_intervallNoConnect;
    RS232_CloseComport(m_globals->comportNumber());
}

void BrewSensorData::setTemperature()
{
    int n = 0;
    QString temp = "301\n";
    QByteArray tempArr = temp.toLocal8Bit();
    char *str = tempArr.data();
    unsigned char buf[5];
    {
        RS232_cputs(m_globals->comportNumber(), str);

        n = RS232_PollComport(m_globals->comportNumber(), buf, 5);
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

void BrewSensorData::setTemperatureNoConnect()
{
    int n = 0;
    QString temp = "301\n";
    QByteArray tempArr = temp.toLocal8Bit();
    char *str = tempArr.data();
    unsigned char buf[6];
    {
        RS232_cputs(m_globals->comportNumber(), str);

        n = RS232_PollComport(m_globals->comportNumber(), buf, 5);
        if (n>0) {
            m_temperature = QString((char *)buf);
            qDebug() << "m_temp: " <<m_temperature;
            qDebug() << "m_time: " <<getTimer();
            qDebug() << "m_total: " <<m_totalTime;
            qDebug() << "m_remaining: " <<m_total->remainingTime();
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
        char *str = speedArray.data();
        RS232_cputs(m_globals->comportNumber(), str);
    }
}

void BrewSensorData::setAutoMotorSpeed(QString step)
{
    qDebug() << step;
    double realSpeed;
    QString speed;
    if (step.startsWith("Aufheizen", Qt::CaseInsensitive)) {
        realSpeed = m_globals->motorspeedHeat() * 2.55;
        m_speed = QString::number(m_globals->motorspeedHeat());
    } else {
        realSpeed = m_globals->motorspeedNormal() * 2.55;
        m_speed = QString::number(m_globals->motorspeedNormal());
    }
    speed = QString::number(realSpeed);
    if (speed.toInt() >= 0 && speed.toInt() <= 255) {
        speed += "\n";
        QByteArray speedArray = speed.toLocal8Bit();
        char *str = speedArray.data();
        RS232_cputs(m_globals->comportNumber(), str);
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
        m_intervall->start(m_globals->intervallTimer() * 1000);
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

void BrewSensorData::setIntervall()
{
    m_intervallNoConnect->start(m_globals->intervallTimer() * 1000);
}

void BrewSensorData::endIntervall()
{
    m_intervallNoConnect->stop();
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
