#ifndef BREWRECIPEMODEL_H
#define BREWRECIPEMODEL_H

#include <QAbstractListModel>

class BrewRecipeList;
class BrewRecipe;
class Globals;

Q_DECLARE_METATYPE(QModelIndex)

class BrewRecipeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(BrewRecipeList *list READ getList WRITE setList)

public:
    BrewRecipeModel(QObject *parent = nullptr);

    virtual ~BrewRecipeModel() override;

    enum {
        number = Qt::UserRole, name, date, amount, brewDura, startTemp, startDura,
        ferulaTemp, ferulaDura, proteaseTemp,proteaseDura, maltoseTemp,
        maltoseDura, sugarTemp, sugarDura, endTemp, endDura
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE bool insertRecipe(QString number = "01",
                                  QString name = "NAME",
                                  QString date = "01-01-2019",
                                  QString amount = "60",
                                  QString startT = "45.0",
                                  QString startD = "10",
                                  QString ferulaT = "45.0",
                                  QString ferulaD = "15",
                                  QString protT = "52.0",
                                  QString protD = "20",
                                  QString maltT = "63.0",
                                  QString maltD = "30",
                                  QString sugarT = "72.0",
                                  QString sugarD = "30",
                                  QString endT = "78.0",
                                  QString endD = "0");

    Q_INVOKABLE bool removeRow(int row);

    virtual QHash<int, QByteArray> roleNames() const override;

    BrewRecipeList *getList() const;
    void setList(BrewRecipeList *list);

    Q_INVOKABLE QVariant at(int index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE bool setAt(int row = 0,
                           QString number = "01",
                           QString name = "NAME",
                           QString date = "01-01-1999",
                           QString amount = "60",
                           QString startT = "45.0",
                           QString startD = "10",
                           QString ferulaT = "45.0",
                           QString ferulaD = "15",
                           QString protT = "52.0",
                           QString protD = "20",
                           QString maltT = "63.0",
                           QString maltD = "30",
                           QString sugarT = "72.0",
                           QString sugarD = "30",
                           QString endT = "78.0",
                           QString endD = "0");

private:
    BrewRecipeList *m_list;

    const Globals *m_globals;
};

#endif // BREWRECIPEMODEL_H
