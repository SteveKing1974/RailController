#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "controller.h"
#include "linestatemodel.h"
#include "tracksectionitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Controller>("com.elmsoft.qmlcomponents", 1, 0, "Controller");
    qmlRegisterUncreatableType<LineStateModel>("com.elmsoft.qmlcomponents", 1, 0, "LineStateModel", "Cannot create type");

    qmlRegisterType<TrackSectionItem>("com.elmsoft.qmlcomponents", 1, 0, "TrackSectionItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
