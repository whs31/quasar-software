#include "entry.h"
#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>
#include <argparse.h>
#include "gui/terminal/debugconsole.h"

void consoleHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
    if(QCoreApplication::closingDown())
        return;

    GUI::DebugConsole::MessageType t;
    bool chop = false;

    switch (type) {
    case QtDebugMsg:
        if(msg.startsWith("$ ")) {
            chop = true;
            t = GUI::TerminalBase::Extra1;
        }
        else
            t = GUI::TerminalBase::Debug;
        break;
    case QtWarningMsg: t = GUI::TerminalBase::Warning; break;
    case QtInfoMsg:
        if(msg.startsWith("$ ")) {
            chop = true;
            t = GUI::TerminalBase::Extra2;
        }
        else
            t = GUI::TerminalBase::Info;
        break;
    case QtCriticalMsg:
    case QtFatalMsg: t = GUI::TerminalBase::Error; break;
    }

    QString res = msg;
    if(chop)
        res.remove(0, 2);

    GUI::DebugConsole::get()->append(res, "[]", t);
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

    return app.exec();
}
