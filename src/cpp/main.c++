#include "entry.h++"
#include "gui/console/console.h++"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qqml.h>


CONSOLE_DECLARE;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CONSOLE_INIT;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/entry.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }
        , Qt::QueuedConnection);
    engine.load(url);

    Entry entry;

    return app.exec();
}
