#ifndef CBREWPROGRESS_H
#define CBREWPROGRESS_H

#include <QObject>

class BrewRecipe;
class BrewProgressData;

/*!
 * \brief The BrewProgress class class to handle the progress bar logic
 */
class BrewProgress : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief BrewProgress standard constructor
     */
    BrewProgress();

    /*!
     * \brief ~BrewProgress standard deconstructor
     */
    virtual ~BrewProgress();

    /*!
     * \brief empty checks if list is empty
     * \return true, if empty
     */
    bool empty();

    /*!
     * \brief removeFirst removes first item and rearranges the remaining list
     * \return true, if successful
     */
    Q_INVOKABLE bool removeFirst();

    /*!
     * \brief size return the size of the list
     * \return int
     */
    Q_INVOKABLE int size();

    /*!
     * \brief name returns the name of the BrewProgressData at given index
     * \param index int
     * \return QString
     */
    Q_INVOKABLE QString name(int index);

    /*!
     * \brief nextName returns the name of the BrewProgressData at given index +1
     * \param index int
     * \return QString
     */
    Q_INVOKABLE QString nextName (int index);

    /*!
     * \brief temperature returns the temperature of the BrewProgressData at given index
     * \param index int
     * \return qreal
     */
    Q_INVOKABLE qreal temperature(int index);

    /*!
     * \brief nextTemperature returns the temperature of the BrewProgressData at given index+1
     * \param index int
     * \return qreal
     */
    Q_INVOKABLE qreal nextTemperature(int index);

    /*!
     * \brief duration returns the duration of the BrewProgressData at given index
     * \param index int
     * \return qreal
     */
    Q_INVOKABLE qreal duration(int index);

    /*!
     * \brief nextDuration returns the duration of the BrewProgressData at given index+1
     * \param index int
     * \return qreal
     */
    Q_INVOKABLE qreal nextDuration(int index);

    /*!
     * \brief setRecipe sets the currently loaded recipe
     * \param recipe BrewRecipe
     */
    Q_INVOKABLE void setRecipe(QString number,
                               QString name,
                               QString date,
                               QString amount,
                               QString startT,
                               QString startD,
                               QString ferulaT,
                               QString ferulaD,
                               QString protT,
                               QString protD,
                               QString maltT,
                               QString maltD,
                               QString sugarT,
                               QString sugarD,
                               QString endT,
                               QString endD);

private:
    /*!
     * \brief m_ProgressQ QQueue to save the brew steps as BrewProgressData
     */
    QList<BrewProgressData*> *m_ProgressList;

    /*!
     * \brief recipe holds the currently loaded recipe to brew
     */
    BrewRecipe *m_recipe;

    /*!
     * \brief initializeProgressQ initialize the Q for brew progress data
     * \param bpd BrewProgressData class
     * \return true, if initialized successful
     */
    bool initializeProgressQ();
};

#endif // CBREWPROGRESS_H
