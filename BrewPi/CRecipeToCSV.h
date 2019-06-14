#ifndef CRECIPETOCSV_H
#define CRECIPETOCSV_H

#include <QVector>

class QFile;
class BrewRecipeList;
class BrewRecipe;
class QString;

class BrewRecipeToCSV
{
public:
    BrewRecipeToCSV();

    ~BrewRecipeToCSV();

    /*!
     * \brief flush flush file
     */
    void flush();

    /*!
     * \brief csvToRecipeList save csv-file recipes to a recipe list
     * \return BrewRecipeList return the complete recipe list
     */
    QVector<BrewRecipe*>* csvToRecipeList();

    QString getName();

    /*!
     * \brief RecipeListToCSV save all recipes to a csv-file
     * \param list vector of type BrewRecipeList
     * \return true, if successful
     */
    bool recipeListToCSV(BrewRecipeList *list);

private:
    /*!
     * \brief m_file csv file
     */
    QFile *m_file;

    /*!
     * \brief RecipeToCSV write the recipe data to the csv file
     * \param recipe BrewRecipe file
     */
    void RecipeToCSV(BrewRecipe* recipe);

    /*!
     * \brief csvToRecipe write the csv data to the recipe
     * \param line line to read from csv file (equals 1 recipe)
     * \return BrewRecipe return the complete recipe
     */
    BrewRecipe* csvToRecipe(QString line);
};

#endif // CRECIPETOCSV_H
