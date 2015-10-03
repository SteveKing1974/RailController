#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "controller.h"
#include "linestatemodel.h"
#include "tracksectionitem.h"
#include "breaksectionitem.h"
#include "pointsectionitem.h"
#include "tracksection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Controller>("com.elmsoft.qmlcomponents", 1, 0, "Controller");
    qmlRegisterUncreatableType<LineStateModel>("com.elmsoft.qmlcomponents", 1, 0, "LineStateModel", "Cannot create type");

    qmlRegisterUncreatableType<TrackSection>("com.elmsoft.qmlcomponents", 1, 0, "TrackSection", "Cannot create type");

    qmlRegisterType<TrackSectionItem>("com.elmsoft.qmlcomponents", 1, 0, "TrackSectionItem");
    qmlRegisterType<BreakSectionItem>("com.elmsoft.qmlcomponents", 1, 0, "BreakSectionItem");
    qmlRegisterType<PointSectionItem>("com.elmsoft.qmlcomponents", 1, 0, "PointSectionItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
