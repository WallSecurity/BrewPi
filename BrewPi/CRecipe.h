#ifndef BREWRECIPE_H
#define BREWRECIPE_H

#include <QObject>
#include <QDate>

class BrewProgress;
class mashRest;

/*!
 * \brief The BrewRecipe class creates a brew recipe consisting of various data
 */
class BrewRecipe : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(int number READ getNumber WRITE setNumber)
//    Q_PROPERTY(QString name READ getName WRITE setName)
//    Q_PROPERTY(QString pdate READ printDate WRITE setpDate)
//    Q_PROPERTY(qreal amount READ getAmount WRITE setAmount)
//    Q_PROPERTY(qreal brewDura READ getBrewDura WRITE setBrewDura)
//    Q_PROPERTY(qreal startTemp READ getStartMashTemp WRITE setStartMashTemp)
//    Q_PROPERTY(int startDura READ getStartMashDura WRITE setStartMashDura)
//    Q_PROPERTY(qreal glucanaseTemp READ getGlucanaseTemp WRITE setGlucanaseTemp)
//    Q_PROPERTY(int glucanaseDura READ getGlucanaseDura WRITE setGlucanaseDura)
//    Q_PROPERTY(qreal ferulaTemp READ getFerulaTemp WRITE setFerulaTemp)
//    Q_PROPERTY(int ferulaDura READ getFerulaDura WRITE setFerulaDura)
//    Q_PROPERTY(qreal proteaseTemp READ getProteaseTemp WRITE setProteaseTemp)
//    Q_PROPERTY(int proteaseDura READ getProteaseDura WRITE setProteaseDura)
//    Q_PROPERTY(qreal maltoseTemp READ getMaltoseTemp WRITE setMaltoseTemp)
//    Q_PROPERTY(int maltoseDura READ getMaltoseDura WRITE setMaltoseDura)
//    Q_PROPERTY(qreal sugarTemp READ getSugarTemp WRITE setSugarTemp)
//    Q_PROPERTY(int sugarDura READ getSugarDura WRITE setSugarDura)
//    Q_PROPERTY(qreal endTemp READ getEndTemp WRITE setEndTemp)
//    Q_PROPERTY(int endDura READ getEndDura)

public:
    BrewRecipe();

    /*!
     * \brief BrewRecipe standard constructor for a complete recipe
     */
    BrewRecipe(int number,
               QString name,
               QDate date,
               qreal amount,
               mashRest start,
               mashRest ferula,
               mashRest protease,
               mashRest maltose,
               mashRest sugar,
               mashRest end);

    /*!
     * \brief BrewRecipe copy another recipe
     */
    BrewRecipe (const BrewRecipe& other);

    virtual ~BrewRecipe();

    /*!
     * \brief minTemp calculate lowest temperature
     * \return qreal
     */
    qreal minTemp();

    /*!
     * \brief maxTemp calculate highest temperature
     * \return
     */
    qreal maxTemp();

    /*!
     * \brief getNumber get the brew number
     * \return brew number
     */
    int getNumber() const;
    /*!
     * \brief setNumber set the brew number
     * \param number new brew number
     */
    void setNumber(int number);

    /*!
     * \brief getName get the brew name
     * \return brew name
     */
    QString getName() const;
    /*!
     * \brief setName set the brew name
     * \param name new brew name
     */
    void setName(const QString &name);

    /*!
     * \brief getDate get the brew date [DD-MM-YYYY]
     * \return brew date [DD-MM-YYYY]
     */
    QDate getDate() const;
    /*!
     * \brief getDate get the brew date [DD-MM-YYYY]
     * \return brew date [DD-MM-YYYY]
     */
    QString printDate() const;
    /*!
     * \brief setDate set the brew date [DD-MM-YYYY]
     * \param date new brew date [DD-MM-YYYY]
     */
    void setDate(const QDate &date);
    /*!
     * \brief setpDate set the brew date [DD-MM-YYYY] with QString
     * \param date new brew date [DD-MM-YYYY] QString
     */
    void setpDate(const QString &date);
    /*!
     * \brief getAmount get brew amount
     * \return amount in liters
     */
    qreal getAmount() const;
    /*!
     * \brief setAmount set brew amount
     * \param Amount qreal
     */
    void setAmount(qreal Amount);

    /*!
     * \brief getBrewDura get total brew duration in minutes
     * \return
     */
    qreal getBrewDura() const;
    /*!
     * \brief setBrewDura set total brew duration
     * \param BrewDura bool
     */
    void setBrewDura();
    void setBrewDura(qreal brewDura);


    /*!
     * \brief getStartMash get the start mash rest
     * \return start mash rest
     */
    mashRest *getStartMash() const;
    /*!
     * \brief getStartMashTemp get start mash temperature [°C]
     * \return start mash temperature [°C]
     */
    qreal getStartMashTemp() const;
    /*!
     * \brief getStartMashDura get start mash rest duration [min]
     * \return start mash rest duration [min]
     */
    qreal getStartMashDura() const;
    /*!
     * \brief setStartMash set start mash temperature
     * \param startMashTemp rest temperature [°C]
     */
    void setStartMashTemp(qreal startMashTemp);
    /*!
     * \brief setStartMash set start mash duration
     * \param startMashDura rest duration [min]
     */
    void setStartMashDura(qreal startMashDura);

    /*!
     * \brief getGlucanase get the glucanase rest
     * \return glucanase rest
     */
//    mashRest *getGlucanase() const;
    /*!
     * \brief getGlucanaseTemp get glucanase rest temperature [°C]
     * \return glucanase rest temperature [°C]
     */
//    qreal getGlucanaseTemp() const;
    /*!
     * \brief getGlucanaseDura get glucanase rest duration [min]
     * \return glucanase rest duration [min]
     */
//    int getGlucanaseDura() const;
    /*!
     * \brief setGlucanase set glucanase temperature
     * \param glucanaseTemp rest temperature [°C]
     */
//    void setGlucanaseTemp(qreal glucanaseTemp);
    /*!
     * \brief setGlucanaseDura set start mash duration
     * \param glucanaseDura rest duration [min]
     */
//    void setGlucanaseDura(int glucanaseDura);

    /*!
     * \brief getFerula get the ferula rest
     * \return ferula rest
     */
    mashRest *getFerula() const;
    /*!
     * \brief getFerulaTemp get ferula rest temperature [°C]
     * \return ferula rest temperature [°C]
     */
    qreal getFerulaTemp() const;
    /*!
     * \brief getFerulaDura get ferula rest duration [min]
     * \return ferula rest duration [min]
     */
    qreal getFerulaDura() const;
    /*!
     * \brief setFerula set ferula rest temperature
     * \param ferulaTemp rest temperature [°C]
     */
    void setFerulaTemp(qreal ferulaTemp);
    /*!
     * \brief setFerulaDura set start mash duration
     * \param ferulaDura rest duration [min]
     */
    void setFerulaDura(qreal ferulaDura);

    /*!
     * \brief getProtease get the protease rest
     * \return protease rest
     */
    mashRest *getProtease() const;
    /*!
     * \brief getProteaseTemp get protease rest temperature [°C]
     * \return protease rest temperature [°C]
     */
    qreal getProteaseTemp() const;
    /*!
     * \brief getProteaseDura get protease rest duration [min]
     * \return protease rest duration [min]
     */
    qreal getProteaseDura() const;
    /*!
     * \brief setProtease set protease rest temperature
     * \param proteaseTemp rest temperature [°C]
     */
    void setProteaseTemp(qreal proteaseTemp);
    /*!
     * \brief setProteaseDura set start mash duration
     * \param proteaseDura rest duration [min]
     */
    void setProteaseDura(qreal proteaseDura);

    /*!
     * \brief getMaltose get the maltose rest
     * \return maltose rest
     */
    mashRest *getMaltose() const;
    /*!
     * \brief getMaltoseTemp get maltose rest temperature [°C]
     * \return maltose rest temperature [°C]
     */
    qreal getMaltoseTemp() const;
    /*!
     * \brief getMaltoseDura get maltose rest duration [min]
     * \return maltose rest duration [min]
     */
    qreal getMaltoseDura() const;
    /*!
     * \brief setMaltose set maltose rest temperature
     * \param maltoseTemp rest temperature [°C]
     */
    void setMaltoseTemp(qreal maltoseTemp);
    /*!
     * \brief setMaltoseDura set start mash duration
     * \param maltoseDura rest temperature [°C]
     */
    void setMaltoseDura(qreal maltoseDura);

    /*!
     * \brief getSugar get the sugar rest
     * \return sugar rest
     */
    mashRest *getSugar() const;
    /*!
     * \brief getSugarTemp get sugar rest temperature [°C]
     * \return sugar rest temperature [°C]
     */
    qreal getSugarTemp() const;
    /*!
     * \brief getSugarDura get sugar rest duration [min]
     * \return sugar rest duration [min]
     */
    qreal getSugarDura() const;
    /*!
     * \brief setSugar set sugar rest temperature
     * \param sugarTemp rest temperature [°C]
     */
    void setSugarTemp(qreal sugarTemp);
    /*!
     * \brief setSugarDura set start mash duration
     * \param sugarDura rest temperature [°C]
     */
    void setSugarDura(qreal sugarDura);

    /*!
     * \brief getEnd get the end rest
     * \return end rest
     */
    mashRest *getEnd() const;
    /*!
     * \brief getEndTemp get end temperature[°C]
     * \return end temperature [°C]
     */
    qreal getEndTemp() const;
    /*!
     * \brief getEndDura get end duration [min]
     * \return end duration [min]
     */
    qreal getEndDura() const;
    /*!
     * \brief setEnd set end mash temperature
     * \param endTemp end mash temperature [°C]
     */
    void setEndTemp(qreal endTemp);

private:
    /*!
     * \brief m_number brew number
     */
    int m_number;
    /*!
     * \brief m_name brew name
     */
    QString m_name;
    /*!
     * \brief m_date brew date
     */
    QDate m_date;
    /*!
     * \brief m_Amount brew amount
     */
    qreal m_Amount;

    /*!
     * \brief m_brewDura total brew length
     */
    qreal m_brewDura;

    /*!
     * \brief m_startMash data for starting the mash
     */
    mashRest *m_startMash;
    /*!
     * \brief m_glucanase data for glucanase rest
     */
//    mashRest *m_glucanase;
    /*!
     * \brief m_ferula data for ferula rest
     */
    mashRest *m_ferula;
    /*!
     * \brief m_protease data for protease rest
     */
    mashRest *m_protease;
    /*!
     * \brief m_maltose data for maltose rest
     */
    mashRest *m_maltose;
    /*!
     * \brief m_sugar data for sugar rest
     */
    mashRest *m_sugar;
    /*!
     * \brief m_end end temperature
     */
    mashRest *m_end;
};

#endif // BREWRECIPE_H
