#ifndef CRECIPELIST_H
#define CRECIPELIST_H

#include <QObject>

class BrewRecipe;

/*!
 * \brief The BrewRecipeList class create a list of brew recipes
 */
class BrewRecipeList : public QObject
{
    Q_OBJECT

public:
    explicit BrewRecipeList(QObject *parent = nullptr);

    explicit BrewRecipeList(QVector<BrewRecipe*> *recipeList);

    virtual ~BrewRecipeList();

    /*!
     * \brief getItems return a vector of all items
     * \return
     */
    QVector<BrewRecipe*>* getItems() const;

    /*!
     * \brief insertAt insert a brew recipe at given index
     * \param index index >= 0
     * \param recipe BrewRecipe to insert
     * \return true, if successful
     */
    bool insertAt(int index, BrewRecipe* &recipe);

    /*!
     * \brief getItemAt return the recipe at given index
     * \param index index >= 0
     * \return BrewRecipe, if successful
     */
    BrewRecipe* getItemAt(int index);

    /*!
     * \brief setItemAt set the item at the index
     * \param index int >= 0
     * \param recipe BrewRecipe
     * \return true, if successful
     */
    bool setItemAt(int index, BrewRecipe &recipe);

    /*!
     * \brief getSize get the size of vector
     * \return size of vecor
     */
    int getSize();

    /*!
     * \brief isEmpty determine whether list is empty
     * \return true, if empty
     */
    bool listEmpty();

signals:
    void ItemAppended();
    void ItemRemoved();

public slots:
    /*!
     * \brief appendItem append a recipe to the end of the vector
     * \param recipe BrewRecipe
     */
    void appendItem(BrewRecipe* &recipe);

    /*!
     * \brief removeItem remove a recipe from the vecor
     * \param recipe BrewRecipe
     */
    bool removeItemAt(int row);

    /*!
     * \brief takeFirstItem return and delete the first item of the vector
     * \return first item of vector
     */
    BrewRecipe* takeFirstItem();

private:
    /*!
     * \brief m_recipeList vector containing BrewRecipes
     */
    QVector<BrewRecipe*> *m_recipeList;
};

#endif // CRECIPELIST_H
