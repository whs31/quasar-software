//#include "entry.h++"

#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/qqml.h>
#include <QtQuick/QQuickWindow>
#include <iostream>

int main(int argc, char* argv[])
{

    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("QuaSAR Emulator");
    QCoreApplication::setApplicationVersion("0.0.1alpha");
    QCoreApplication::setOrganizationName("Radar-MMS");;
    qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

    const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
    //Entry entry;

    QQmlEngine engine;
    QObject::connect(&engine, &QQmlEngine::quit, qApp, &QCoreApplication::quit);

    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    component.loadUrl(qml_entry);
    if(component.isReady())
        component.create();
    else
    {
        qInstallMessageHandler(0);
        qCritical() << "FATAL QML ERROR: " << component.errorString();
    }

    return app.exec();
}
