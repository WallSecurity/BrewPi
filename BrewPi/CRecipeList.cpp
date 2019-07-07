#include "CRecipeList.h"
#include "CRecipe.h"
#include <QVector>
#include "CRecipeToCSV.h"

BrewRecipeList::BrewRecipeList(QObject *parent) :
    QObject (parent)
{
    m_recipeList = new QVector<BrewRecipe*>();
}

BrewRecipeList::BrewRecipeList(QVector<BrewRecipe *> *recipeList)
{
    m_recipeList = new QVector<BrewRecipe*>(*recipeList);
}

BrewRecipeList::~BrewRecipeList()
{
    delete m_recipeList;
}

QVector<BrewRecipe*>* BrewRecipeList::getItems() const
{
    return m_recipeList;
}

bool BrewRecipeList::insertAt(int index, BrewRecipe* &recipe)
{
    if (index < 0 || index > m_recipeList->size())
        return false;

    m_recipeList->insert(index, recipe);
    return true;
}

BrewRecipe* BrewRecipeList::getItemAt(int index)
{
    if (index < 0 || index > m_recipeList->size())
        return nullptr;

    return m_recipeList->at(index);
}

bool BrewRecipeList::setItemAt(int index, BrewRecipe &recipe)
{
    if (index < 0 || index > m_recipeList->size())
        return false;

    BrewRecipe *oldRecipe = m_recipeList->at(index);

    if (recipe.getNumber() == oldRecipe->getNumber() &&
            recipe.getName() == oldRecipe->getName() &&
            recipe.getDate() == oldRecipe->getDate() &&
            recipe.getAmount() == oldRecipe->getAmount() &&
            recipe.getBrewDura() == oldRecipe->getBrewDura() &&
            recipe.getStartMashTemp() == oldRecipe->getStartMashTemp() &&
            recipe.getStartMashDura() == oldRecipe->getStartMashDura() &&
            recipe.getFerulaTemp() == oldRecipe->getFerulaTemp() &&
            recipe.getFerulaDura() == oldRecipe->getFerulaDura() &&
            recipe.getProteaseTemp() == oldRecipe->getProteaseTemp() &&
            recipe.getProteaseDura() == oldRecipe->getProteaseDura() &&
            recipe.getMaltoseTemp() == oldRecipe->getMaltoseTemp() &&
            recipe.getMaltoseDura() == oldRecipe->getMaltoseDura() &&
            recipe.getSugarTemp() == oldRecipe->getSugarTemp() &&
            recipe.getSugarDura() == oldRecipe->getSugarDura() &&
            recipe.getEndTemp() == oldRecipe->getEndTemp() &&
            recipe.getEndDura() == oldRecipe->getEndDura()
            )
        return false;

    oldRecipe->setNumber(recipe.getNumber());
    oldRecipe->setName(recipe.getName());
    oldRecipe->setDate(recipe.getDate());
    oldRecipe->setAmount(recipe.getAmount());
    oldRecipe->setBrewDura(recipe.getBrewDura());
    oldRecipe->setStartMashTemp(recipe.getStartMashTemp());
    oldRecipe->setStartMashDura(recipe.getStartMashDura());
    oldRecipe->setFerulaTemp(recipe.getFerulaTemp());
    oldRecipe->setFerulaDura(recipe.getFerulaDura());
    oldRecipe->setProteaseTemp(recipe.getProteaseTemp());
    oldRecipe->setProteaseDura(recipe.getProteaseDura());
    oldRecipe->setMaltoseTemp(recipe.getMaltoseTemp());
    oldRecipe->setMaltoseDura(recipe.getMaltoseDura());
    oldRecipe->setSugarTemp(recipe.getSugarTemp());
    oldRecipe->setSugarDura(recipe.getSugarDura());
    oldRecipe->setEndTemp(recipe.getEndTemp());
    return true;
}

int BrewRecipeList::getSize()
{
    return m_recipeList->size();
}

bool BrewRecipeList::listEmpty()
{
    return m_recipeList->empty();
}

void BrewRecipeList::appendItem(BrewRecipe* &recipe)
{
    m_recipeList->append(recipe);
    emit ItemAppended();
}

bool BrewRecipeList::removeItemAt(int row)
{
    if (row < 0 || row > m_recipeList->size())
        return false;

    m_recipeList->removeAt(row);
    emit ItemRemoved();
    return true;
}

BrewRecipe* BrewRecipeList::takeFirstItem()
{
    if (m_recipeList->empty())
        return nullptr;

    emit ItemRemoved();
    return m_recipeList->takeFirst();
}
