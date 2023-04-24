#include "entry.h++"
#include "gui/console/console.h++"

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>

CONSOLE_DECLARE;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setOrganizationName("Radar-MMS");
    qInstallMessageHandler(consoleHandler);
    qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

    Entry entry;

    CONSOLE_INIT;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl)
        {
            if (not obj and url == objUrl)
                QCoreApplication::exit(-1);
        }
        , Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
