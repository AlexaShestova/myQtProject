#include "mydata.h"
#include "controller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    srand(time(0));
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MyData *data = new MyData(100,100,&engine);
    Controller *controller = new Controller(data);
    controller->startGame();

    engine.rootContext()->setContextProperty("MyData", data);
    engine.rootContext()->setContextProperty("MyController", controller);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
