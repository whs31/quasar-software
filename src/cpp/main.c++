#include "entry.h"
#include "gui/console/console.h"

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>
#include <argparse.h>

Console* console = nullptr;
QList<QString> cachedDebugInfo;
bool releaseCacheFlag = false;
bool start_console = false;
void consoleHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
    QString txt;

    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg("<font color=\"#b8c0e0\">" + msg + "</font>");
        break;
    case QtWarningMsg:
        txt = QString("%1").arg("<font color=\"#eed49f\">" + msg + "</font>");
        break;
    case QtInfoMsg:
        if(msg.startsWith("$"))
            txt = QString("%1").arg("<font color=\"#c6a0f6\">" + msg.right(msg.size() - 2) + "</font>");
        else
            txt = QString("%1").arg("<font color=\"#8bd5ca\">" + msg + "</font>");
        break;
    case QtCriticalMsg:
        txt = QString("%1").arg("<font color=\"#ee99a0\">" + msg + "</font>");
        break;
    case QtFatalMsg:
        txt = QString("%1").arg("<font color=\"#ee99a0\">" + msg + "</font>");
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

static const char *const usages[] = {
    "basic [options] [[--] args]",
    "basic [options]",
    NULL,
};

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setOrganizationName(PROJECT_COMPANY);

    int no_console = 0;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN(0, "no-log-redirect", &no_console, "disable internal console and log into external terminal", NULL, 0, 0),
        OPT_END(),
    };
    struct argparse argparse;
    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nQuaSAR SAR control software.", "\n(c) 2023 Radar-MMS");
    argc = argparse_parse(&argparse, argc, (const char**)argv);

    if(not no_console)
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
