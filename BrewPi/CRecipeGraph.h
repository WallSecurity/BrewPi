#ifndef CRECIPEGRAPH_H
#define CRECIPEGRAPH_H

#include <QObject>
#include <QtCharts>

class BrewRecipe;
class Globals;

using namespace QtCharts;

class BrewRecipeGraph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QLineSeries *series READ series WRITE setSeries NOTIFY seriesChanged)
public:
    explicit BrewRecipeGraph(const Globals &globals, QObject *parent = nullptr);

    virtual ~BrewRecipeGraph();

    enum {number, name, date, amount, brewDura, startTemp, startDura,
        ferulaTemp, ferulaDura, proteaseTemp,proteaseDura, maltoseTemp,
        maltoseDura, sugarTemp, sugarDura, endTemp, endDura
    };

    /*!
     * \brief series internal series
     * \return QLineSeries
     */
    QLineSeries* series();

    /*!
     * \brief getX return x value
     * \param index position
     * \return qreal
     */
    Q_INVOKABLE qreal getX(int index) const;

    /*!
     * \brief getY return y value
     * \param index position
     * \return qreal
     */
    Q_INVOKABLE qreal getY(int index) const;

    /*!
     * \brief setSeries assign new series
     * \param series QLineSeries
     */
    void setSeries(QLineSeries* series);

    /*!
     * \brief getTotalX get the last x point
     * \return highest x
     */
    Q_INVOKABLE qreal getTotalX() const;

    /*!
     * \brief getMinY get the min y point
     * \return smallest y
     */
    Q_INVOKABLE qreal getMinY() const;

    /*!
     * \brief getMaxY get the man y point
     * \return highest y
     */
    Q_INVOKABLE qreal getMaxY() const;

    /*!
     * \brief getSize size of the QLineSeries
     * \return int
     */
    Q_INVOKABLE int getSize();

    Q_INVOKABLE void recipeToSeries(
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

    /*!
     * \brief clearSeries empty the series
     */
    Q_INVOKABLE void clearSeries();

    /*!
     * \brief getRecipe returns the currently loaded recipe
     * \return  BrewRecipe
     */
    Q_INVOKABLE BrewRecipe *getRecipe() const;

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

    /*!
     * \brief getData returns specific recipe data
     * \param role specify which data to return via enumeration
     */
    Q_INVOKABLE QVariant getData(int role);

signals:
    void seriesChanged();
    void dataChanged();

private:
    /*!
     * \brief m_series storing the series of points
     */
    QLineSeries* m_series;

    /*!
     * \brief recipe holds the currently loaded recipe to brew
     */
    BrewRecipe *m_recipe;

    /*!
     * \brief m_globals global variables manager
     */
    const Globals *m_globals;
};

#endif // CRECIPEGRAPH_H
