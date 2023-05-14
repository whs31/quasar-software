#include "entry.h"
#include "gui/console/console.h"

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

Console* console = nullptr;
QList<QString> cachedDebugInfo;
bool releaseCacheFlag = false;
bool start_console = false;
void consoleHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
    QString txt;

    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg("<font color=\"#ECEFF4\">" + msg + "</font>");
        break;
    case QtWarningMsg:
        txt = QString("%1").arg("<font color=\"#EBCB8B\">" + msg + "</font>");
        break;
    case QtInfoMsg:
        if(msg.startsWith("$"))
            txt = QString("%1").arg("<font color=\"#B48EAD\">" + msg + "</font>");
        else
            txt = QString("%1").arg("<font color=\"#8FBCBB\">" + msg + "</font>");
        break;
    case QtCriticalMsg:
        txt = QString("%1").arg("<font color=\"#BF616A\">" + msg + "</font>");
        break;
    case QtFatalMsg:
        txt = QString("%1").arg("<font color=\"#D08770\">" + msg + "</font>");
        break;
    }

    if(start_console and console != nullptr)
    {
        console->append(txt);
        if (not releaseCacheFlag)
        {
            releaseCacheFlag = true;
            for (const auto &message : cachedDebugInfo)
                console->append(message);
        }
    }
    else
        cachedDebugInfo.append(txt);
};

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setOrganizationName("Radar-MMS");
    qInstallMessageHandler(consoleHandler);
    qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

    const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    QQuickStyle::setStyle("Material");

    Console console_instance;
    console = &console_instance;

    Entry entry;

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

    start_console = true;
    return app.exec();
}
