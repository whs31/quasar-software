#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/qqml.h>
#include <QtQuick/QQuickWindow>
#include <QQuickStyle>

#include "telemetry/telemetryemulator.h++"
#include "telemetry/telemetrysocketemulator.h++"
#include "execd/feedbackemulator.h++"

int main(int argc, char* argv[])
{

    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("QuaSAR Emulator");
    QCoreApplication::setApplicationVersion("0.0.1alpha");
    QCoreApplication::setOrganizationName("Radar-MMS");;
    qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

    const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    QQuickStyle::setStyle("Material");

    TelemetryEmulator emulator;
    Debug::TelemetrySocketEmulator telsrv(&emulator);
    Debug::FeedbackEmulator feedback(&emulator);
    qmlRegisterSingletonInstance<TelemetryEmulator>("Telemetry", 1, 0, "Telemetry", &emulator);
    qmlRegisterSingletonInstance<Debug::TelemetrySocketEmulator>("Telemetry", 1, 0, "TelemetrySocket", &telsrv);
    qmlRegisterSingletonInstance<Debug::FeedbackEmulator>("Execd", 1, 0, "Feedback", &feedback);

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
