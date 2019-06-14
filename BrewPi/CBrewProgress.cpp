#include "CBrewProgress.h"
#include "CBrewProgressData.h"
#include "CRecipe.h"
#include "globalsConstants.h"
#include "CMashRest.h"
#include <QList>

BrewProgress::BrewProgress()
{
    m_ProgressList = new QList<BrewProgressData*>();
    m_recipe = new BrewRecipe();
}

BrewProgress::~BrewProgress()
{
    delete m_ProgressList;
    delete m_recipe;
}

bool BrewProgress::empty()
{
    return m_ProgressList->isEmpty();
}

bool BrewProgress::removeFirst()
{
    if (m_ProgressList->isEmpty()) {
        return false;
    } else {
        m_ProgressList->removeFirst();
        //        QList<BrewProgressData*>::iterator i;
        //        for (i = m_ProgressList->begin(); i != m_ProgressList->end(); i++) {
        //        }
        return true;
    }
}


int BrewProgress::size()
{
    return m_ProgressList->size();
}

QString BrewProgress::name(int index)
{
    if (index >= 0 && index < m_ProgressList->size()) {
        return m_ProgressList->at(index)->name();
    } else {
        return "";
    }
}

QString BrewProgress::nextName(int index)
{
    if (index >= 0 && index < m_ProgressList->size()-1) {
        return m_ProgressList->at(index+1)->name();
    } else {
        return "";
    }
}

qreal BrewProgress::temperature(int index)
{
    if (index >= 0 && index < m_ProgressList->size()) {
        return m_ProgressList->at(index)->temperature();
    } else {
        return -1;
    }
}

qreal BrewProgress::nextTemperature(int index)
{
    if (index >= 0 && index < m_ProgressList->size()-1) {
        return m_ProgressList->at(index+1)->temperature();
    } else {
        return -1;
    }
}

qreal BrewProgress::duration(int index)
{
    if (index >= 0 && index < m_ProgressList->size()) {
        return m_ProgressList->at(index)->duration();
    } else {
        return -1;
    }
}

qreal BrewProgress::nextDuration(int index)
{
    if (index >= 0 && index < m_ProgressList->size()-1) {
        return m_ProgressList->at(index+1)->duration();
    } else {
        return -1;
    }
}

void BrewProgress::setRecipe(QString number, QString name, QString date, QString amount, QString startT, QString startD, QString ferulaT, QString ferulaD, QString protT, QString protD, QString maltT, QString maltD, QString sugarT, QString sugarD, QString endT, QString endD)
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

    initializeProgressQ();
}

bool BrewProgress::initializeProgressQ()
{
    m_ProgressList->clear();
    if (m_recipe == nullptr) {
        return false;
    } else {

        BrewProgressData *q_data = nullptr;
        qreal heatDuration = 0;

        //start
        if (m_recipe->getStartMashDura() > 0) {
            q_data = new BrewProgressData("Einmaischen", m_recipe->getStartMashTemp(), m_recipe->getStartMashDura());
            m_ProgressList->append(q_data);
        }

        //ferula
        if (m_recipe->getFerulaDura() > 0) {
            if (!m_ProgressList->isEmpty()) {
                if (m_recipe->getFerulaTemp() - m_ProgressList->last()->temperature() > 0) {
                    heatDuration = (m_recipe->getFerulaTemp() - m_ProgressList->last()->temperature()) * HEATING_MULTIPLIERSF;
                } else {
                    heatDuration = 0;
                }
            } else {
                heatDuration = m_recipe->getFerulaTemp() * HEATING_MULTIPLIERSF;
            }
            if (heatDuration > 0) {
                q_data = new BrewProgressData("Aufheizen -> Weizen-Rast", m_recipe->getFerulaTemp(), heatDuration);
                m_ProgressList->append(q_data);
            }
            q_data = new BrewProgressData("Weizen-Rast", m_recipe->getFerulaTemp(), m_recipe->getFerulaDura());
            m_ProgressList->append(q_data);
        }

        //protease
        if (m_recipe->getProteaseDura() > 0) {
            if (!m_ProgressList->isEmpty()) {
                if (m_recipe->getProteaseTemp() - m_ProgressList->last()->temperature() > 0) {
                    heatDuration = (m_recipe->getProteaseTemp() - m_ProgressList->last()->temperature()) * HEATING_MULTIPLIERFP;
                } else {
                    heatDuration = 0;
                }
            } else {
                heatDuration = m_recipe->getProteaseTemp() * HEATING_MULTIPLIERFP;
            }
            if (heatDuration > 0) {
                q_data = new BrewProgressData("Aufheizen -> Protease-Rast", m_recipe->getProteaseTemp(), heatDuration);
                m_ProgressList->append(q_data);
            }
            q_data = new BrewProgressData("Protease-Rast", m_recipe->getProteaseTemp(), m_recipe->getProteaseDura());
            m_ProgressList->append(q_data);
        }

        //Maltose
        if (m_recipe->getMaltoseDura() > 0) {
            if (!m_ProgressList->isEmpty()) {
                if (m_recipe->getMaltoseTemp() - m_ProgressList->last()->temperature() > 0) {
                    heatDuration = (m_recipe->getMaltoseTemp() - m_ProgressList->last()->temperature()) * HEATING_MULTIPLIERPM;
                } else {
                    heatDuration = 0;
                }
            } else {
                heatDuration = m_recipe->getMaltoseTemp() * HEATING_MULTIPLIERPM;
            }
            if (heatDuration > 0) {
                q_data = new BrewProgressData("Aufheizen -> Maltose-Rast", m_recipe->getMaltoseTemp(), heatDuration);
                m_ProgressList->append(q_data);
            }
            q_data = new BrewProgressData("Maltose-Rast", m_recipe->getMaltoseTemp(), m_recipe->getMaltoseDura());
            m_ProgressList->append(q_data);
        }

        //Sugar
        if (m_recipe->getSugarDura() > 0) {
            if (!m_ProgressList->isEmpty()) {
                if (m_recipe->getSugarTemp() - m_ProgressList->last()->temperature() > 0) {
                    heatDuration = (m_recipe->getSugarTemp() - m_ProgressList->last()->temperature()) * HEATING_MULTIPLIERMS;
                } else {
                    heatDuration = 0;
                }
            } else {
                heatDuration = m_recipe->getSugarTemp() * HEATING_MULTIPLIERMS;
            }
            if (heatDuration > 0) {
                q_data = new BrewProgressData("Aufheizen -> Zucker-Rast", m_recipe->getSugarTemp(), heatDuration);
                m_ProgressList->append(q_data);
            }
            q_data = new BrewProgressData("Zucker-Rast", m_recipe->getSugarTemp(), m_recipe->getSugarDura());
            m_ProgressList->append(q_data);
        }

        //End
        if (m_recipe->getEndTemp() > 0) {
            if (!m_ProgressList->isEmpty()) {
                if (m_recipe->getEndTemp() - m_ProgressList->last()->temperature() > 0) {
                    heatDuration = (m_recipe->getEndTemp() - m_ProgressList->last()->temperature()) * HEATING_MULTIPLIERSE;
                } else {
                    heatDuration = 0;
                }
            } else {
                heatDuration = m_recipe->getEndTemp() * HEATING_MULTIPLIERSE;
            }
            if (heatDuration > 0) {
                q_data = new BrewProgressData("Aufheizen -> Abmaischen", m_recipe->getEndTemp(), heatDuration);
                m_ProgressList->append(q_data);
            }
        }
        delete q_data;
        return true;
    }
}

