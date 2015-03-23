#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "remoteping.h"
#include "linestatemodel.h"

#include "commandclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<LineStateModel>("com.elmsoft.qmlcomponents", 1, 0, "LineStateModel");

    QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    //RemotePing pinger;
    CommandClient c;

    return app.exec();
}
