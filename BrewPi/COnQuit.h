#ifndef CONQUIT_H
#define CONQUIT_H

#include <QObject>

class BrewRecipeList;

class OnQuit : public QObject
{
    Q_OBJECT
public:
    explicit OnQuit(QObject *parent = nullptr);

    ~OnQuit();

    /*!
     * \brief setList assign a list
     * \param list BrewRecipeList
     */
    void setList(BrewRecipeList &list);

signals:

public slots:
    void saveToCSV();

private:
    BrewRecipeList *m_list;
};

#endif // CONQUIT_H
