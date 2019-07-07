#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QIcon>

#include "CSensorData.h"
#include "CRecipeGraph.h"
#include "CRecipeModel.h"
#include "CRecipeList.h"
#include "CRecipe.h"
#include "CRecipeToCSV.h"
#include "CGlobals.h"
#include "COnQuit.h"
#include "rs232.h"
#include "CEnumeration.h"
#include "CBrewProgress.h"
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("../BrewPi/pictures/windowIcon.jpg"));

    Globals *globals = new Globals();
    qDebug() << "Globals initialised";

    qmlRegisterType<BrewRecipeModel>("brewpi.recipemodel", 1, 0, "BrewRecipeModel");
    qmlRegisterUncreatableType<BrewRecipeList>("brewpi.recipelist", 1, 0, "BrewRecipeList",
                                               "BrewRecipeList cannot be created in qml");
    qRegisterMetaType<Enumeration>("Enum");
    qmlRegisterUncreatableType<EnumerationClass>("brewpi.enum", 1, 0, "Enum",
                                               "EnumerationClass cannot be created in qml");

    qDebug() << "Types registered";

    BrewSensorData *temp = new BrewSensorData(*globals);
    qDebug() << "Sensor data created";

    BrewRecipeGraph *recipeGraph = new BrewRecipeGraph(*globals);
    qDebug() << "Recipe graph created";
    BrewProgress *progress = new BrewProgress(*globals);
    qDebug() << "Brew Progress created";

    BrewRecipeToCSV *csvFile = new BrewRecipeToCSV();
    qDebug() << "csvFile created";
    BrewRecipeList *recipeList = new BrewRecipeList(csvFile->csvToRecipeList());
    qDebug() << "Recipelist created with " << recipeList->getSize() << " items";
    qDebug() << "recipe list filled with csv data";
    csvFile->~BrewRecipeToCSV();
    qDebug() << "csvFile closed";

    OnQuit *csvQuit = new OnQuit();
    qDebug() << "quit created";
    csvQuit->setList(*recipeList);
    qDebug() << "onQuit list set";
    QObject::connect(&app, SIGNAL(aboutToQuit()), csvQuit, SLOT(saveToCSV()));
    qDebug() << "signal connected";
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("RecipeList", recipeList);
    engine.rootContext()->setContextProperty("RecipeGraph", recipeGraph);
    engine.rootContext()->setContextProperty("SensorData", temp);
    engine.rootContext()->setContextProperty("ProgressClass", progress);
    engine.rootContext()->setContextProperty("Globals", globals);
    qDebug() << "Properties set";
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qDebug() << "engine started";
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
