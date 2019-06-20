#include "CRecipeGraph.h"
#include "CGlobals.h"
#include "CRecipe.h"
#include "CMashRest.h"
#include <QVector>


BrewRecipeGraph::BrewRecipeGraph(const Globals &globals, QObject *parent) :
    QObject(parent)
{
    m_series = new QLineSeries();
    m_recipe = new BrewRecipe();
    m_globals = &globals;
}

BrewRecipeGraph::~BrewRecipeGraph()
{
    delete m_series;
    delete m_recipe;
}

QLineSeries *BrewRecipeGraph::series()
{
    return m_series;
}

qreal BrewRecipeGraph::getX(int index) const
{
    return m_series->at(index).x();
}

qreal BrewRecipeGraph::getY(int index) const
{
    return m_series->at(index).y();
}

void BrewRecipeGraph::setSeries(QLineSeries* series)
{
    m_series = series;
    emit seriesChanged();
}

qreal BrewRecipeGraph::getTotalX() const
{
    if (m_series->at(m_series->count()-1).isNull())
        return -2;
    return m_series->at(m_series->count()-1).x();
}

qreal BrewRecipeGraph::getMinY() const
{
    qreal min = 5;
    if (!m_series->at(0).isNull()) {
        min = m_series->at(0).y();;
        for (int i = 1; i < m_series->count(); ++i) {
            if (m_series->at(i).y() < min)
                min = m_series->at(i).y();
        }
    }
    return min;
}

qreal BrewRecipeGraph::getMaxY() const
{
    qreal max = -5;
    if (!m_series->at(0).isNull()) {
        max = m_series->at(0).y();;
        for (int i = 1; i < m_series->count(); ++i) {
            if (m_series->at(i).y() > max)
                max = m_series->at(i).y();
        }
    }
    return max;
}

int BrewRecipeGraph::getSize()
{
    return m_series->count();
}

void BrewRecipeGraph::recipeToSeries(QString startT, QString startD, QString ferulaT, QString ferulaD, QString protT, QString protD, QString maltT, QString maltD, QString sugarT, QString sugarD, QString endT, QString endD)
{
    clearSeries();
    //start
    QPointF heat(0, 0);
    QPointF rest(0, 0);

    if (startT.toDouble() > 0) {
        heat.rx() = 0;
        heat.ry() = startT.toDouble();
        m_series->append(heat); //begin start rest

        rest.rx() = startD.toDouble();
        rest.ry() = startT.toDouble();
        m_series->append(rest); //end start rest
    }

    //glucanase
//    if (glucaT.toDouble() > 0) {
//        heat.rx() = rest.x() + (abs((glucaT.toDouble() - rest.y())) * HEATING_MULTIPLIER);
//        heat.ry() = glucaT.toDouble();
//        m_series->append(heat); //heat to ferula rest

//        rest.rx() = heat.x() + glucaD.toDouble();
//        rest.ry() = glucaT.toDouble();
//        m_series->append(rest); //glucanase rest

//    }

    //ferula
    if (ferulaT.toDouble() > 0) {
        heat.rx() = rest.x() + ((ferulaT.toDouble() - rest.y()) * m_globals->heatingMultiplierStartFerula());
        heat.ry() = ferulaT.toDouble();
        m_series->append(heat); //heat to protease rest

        rest.rx() = heat.x() + ferulaD.toDouble();
        rest.ry() = ferulaT.toDouble();
        m_series->append(rest); //ferula rest
    }

    //protease
    if (protT.toDouble() > 0) {
        heat.rx() = rest.x() + ((protT.toDouble() - rest.y()) * m_globals->heatingMultiplierFerulaProtease());
        heat.ry() = protT.toDouble();
        m_series->append(heat); //heat to maltose rest

        rest.rx() = heat.x() + protD.toDouble();
        rest.ry() = protT.toDouble();
        m_series->append(rest); //protease rest
    }

    //maltose
    if (maltT.toDouble() > 0) {
        heat.rx() = rest.x() + ((maltT.toDouble() - rest.y()) * m_globals->heatingMultiplierProteaseMaltose());
        heat.ry() = maltT.toDouble();
        m_series->append(heat); //heat to sugar rest

        rest.rx() = heat.x() + maltD.toDouble();
        rest.ry() = maltT.toDouble();
        m_series->append(rest); //maltose rest
    }

    //sugar
    if (sugarT.toDouble() > 0) {
        heat.rx() = rest.x() + ((sugarT.toDouble() - rest.y()) * m_globals->heatingMultiplierMaltoseSugar());
        heat.ry() = sugarT.toDouble();
        m_series->append(heat); //heat to end

        rest.rx() = heat.x() + sugarD.toDouble();
        rest.ry() = sugarT.toDouble();
        m_series->append(rest); //sugar rest
    }

    //end
    if (endT.toDouble() > 0) {
        heat.rx() = rest.x() + ((endT.toDouble() - rest.y()) * m_globals->heatingMultiplierSugarEnd());
        heat.ry() = endT.toDouble();
        m_series->append(heat); //end

        if (endD.toDouble() > 0) {
            rest.rx() = heat.x() + endD.toDouble();
            rest.ry() = endT.toDouble();
            m_series->append(rest); //end rest
        }
    }
    emit seriesChanged();
}

void BrewRecipeGraph::clearSeries()
{
    m_series->clear();
}

BrewRecipe *BrewRecipeGraph::getRecipe() const
{
    return m_recipe;
}

void BrewRecipeGraph::setRecipe(QString number, QString name, QString date, QString amount, QString startT, QString startD, QString ferulaT, QString ferulaD, QString protT, QString protD, QString maltT, QString maltD, QString sugarT, QString sugarD, QString endT, QString endD)
{
    QDate nDate = QDate::fromString(date, "dd-MM-yyyy");

    mashRest *startMash = new mashRest(startT.toDouble(), startD.toDouble());
    mashRest *ferula = new mashRest(ferulaT.toDouble(), ferulaD.toDouble());
    mashRest *protease = new mashRest(protT.toDouble(), protD.toDouble());
    mashRest *maltose = new mashRest(maltT.toDouble(), maltD.toDouble());
    mashRest *sugar = new mashRest(sugarT.toDouble(), sugarD.toDouble());
    mashRest *end = new mashRest(endT.toDouble(), endD.toDouble());

    m_recipe = new BrewRecipe(number.toInt(), name, nDate, amount.toDouble(),
                                        *startMash, *ferula, *protease, *maltose, *sugar, *end);

    qDebug() << "Recipe successfuly set up";

    m_recipe->setBrewDura();

    emit dataChanged();
}

QVariant BrewRecipeGraph::getData(int role)
{
    switch (role) {
    case number:
        return QVariant(m_recipe->getNumber());
    case name:
        return QVariant(m_recipe->getName());
    case date:
        return QVariant(m_recipe->printDate());
    case amount:
        return QVariant(m_recipe->getAmount());
    case brewDura:
        return QVariant(m_recipe->getBrewDura());
    case startTemp:
        return QVariant(m_recipe->getStartMashTemp());
    case startDura:
        return QVariant(m_recipe->getStartMashDura());
    case ferulaTemp:
        return QVariant(m_recipe->getFerulaTemp());
    case ferulaDura:
        return QVariant(m_recipe->getFerulaDura());
    case proteaseTemp:
        return QVariant(m_recipe->getProteaseTemp());
    case proteaseDura:
        return QVariant(m_recipe->getProteaseDura());
    case maltoseTemp:
        return QVariant(m_recipe->getMaltoseTemp());
    case maltoseDura:
        return QVariant(m_recipe->getMaltoseDura());
    case sugarTemp:
        return QVariant(m_recipe->getSugarTemp());
    case sugarDura:
        return QVariant(m_recipe->getSugarDura());
    case endTemp:
        return QVariant(m_recipe->getEndTemp());
    case endDura:
        return QVariant(m_recipe->getEndDura());
    }
    return QVariant();
}
