#ifndef CGLOBALS_H
#define CGLOBALS_H

#include <QObject>

class QFile;

class Globals : public QObject
{
    Q_OBJECT
public:
    explicit Globals(QObject *parent = nullptr);
    virtual ~Globals();

    Q_INVOKABLE bool saveSettingsToFile();

    bool loadSettingsFromFile();

    Q_INVOKABLE qreal heatingMultiplierStartFerula() const;
    Q_INVOKABLE void setHeatingMultiplierStartFerula(const qreal &heatingMultiplierStartFerula);

    Q_INVOKABLE qreal heatingMultiplierFerulaProtease() const;
    Q_INVOKABLE void setHeatingMultiplierFerulaProtease(const qreal &heatingMultiplierFerulaProtease);

    Q_INVOKABLE qreal heatingMultiplierProteaseMaltose() const;
    Q_INVOKABLE void setHeatingMultiplierProteaseMaltose(const qreal &heatingMultiplierProteaseMaltose);

    Q_INVOKABLE qreal heatingMultiplierMaltoseSugar() const;
    Q_INVOKABLE void setHeatingMultiplierMaltoseSugar(const qreal &heatingMultiplierMaltoseSugar);

    Q_INVOKABLE qreal heatingMultiplierSugarEnd() const;
    Q_INVOKABLE void setHeatingMultiplierSugarEnd(const qreal &heatingMultiplierSugarEnd);

    Q_INVOKABLE int comportNumber() const;
    Q_INVOKABLE void setComportNumber(int comportNumber);

    Q_INVOKABLE int intervallTimer() const;
    Q_INVOKABLE void setIntervallTimer(int intervallTimer);

    Q_INVOKABLE qreal motorspeedHeat() const;
    Q_INVOKABLE void setMotorspeedHeat(const qreal &motorspeedHeat);

    Q_INVOKABLE qreal motorspeedNormal() const;
    Q_INVOKABLE void setMotorspeedNormal(const qreal &motorspeedNormal);



private:
    qreal m_heatingMultiplierStartFerula;
    qreal m_heatingMultiplierFerulaProtease;
    qreal m_heatingMultiplierProteaseMaltose;
    qreal m_heatingMultiplierMaltoseSugar;
    qreal m_heatingMultiplierSugarEnd;
    int m_comportNumber; //24
    int m_intervallTimer; //1.0
    qreal m_motorspeedHeat; //75.0
    qreal m_motorspeedNormal; //50.0

    /*!
     * \brief m_file local file to save/load data to/from
     */
    QFile *m_file;
};

#endif // CGLOBALS_H
