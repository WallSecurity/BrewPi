#include "COnQuit.h"
#include "CRecipeList.h"
#include "CRecipeToCSV.h"

OnQuit::OnQuit(QObject *parent) :
    QObject(parent),
    m_list(nullptr)
{
}

OnQuit::~OnQuit()
{

}

void OnQuit::setList(BrewRecipeList &list)
{
    m_list = &list;
}

void OnQuit::saveToCSV()
{
    BrewRecipeToCSV *csvSaver = new BrewRecipeToCSV();
    csvSaver->recipeListToCSV(m_list);
}

