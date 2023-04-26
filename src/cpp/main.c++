#include "entry.h++"
#include "gui/console/console.h++"
#include "gui/imgui/imguiexample.h++"
#include "scenegraph/imgui/imguiitem.h++"

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/qqml.h>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

Console* console = nullptr;
QList<QString> cachedDebugInfo;
bool releaseCacheFlag = false;
void consoleHandler(QtMsgType type, const QMessageLogContext &,
                    const QString &msg) {
    QString txt;
    int msgt = 0;
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg("<font color=\"#ECEFF4\">" + msg + "</font>");
        msgt = 0;
        break;
    case QtWarningMsg:
        txt = QString("%1").arg("<font color=\"#EBCB8B\">" + msg + "</font>");
        msgt = 2;
        break;
    case QtInfoMsg:
        txt = QString("%1").arg("<font color=\"#8FBCBB\">" + msg + "</font>");
        msgt = 1;
        break;
    case QtCriticalMsg:
        txt = QString("%1").arg("<font color=\"#BF616A\">" + msg + "</font>");
        msgt = 3;
        break;
    case QtFatalMsg:
        txt = QString("%1").arg("<font color=\"#D08770\">" + msg + "</font>");
        msgt = 4;
        break;
    }
    if (console) {
        console->append(txt);
        if (not releaseCacheFlag) {
            releaseCacheFlag = true;
            for (auto message : qAsConst(cachedDebugInfo)) {
                console->append(message);
            }
        }
    } else
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
    Entry entry;

    qmlRegisterType<ImGuiItem>("ImGUI", 1, 0, "ImGUI");
    qmlRegisterType<ImGuiExample>("ImGuiExample", 1, 0, "ImGuiExample");

    Console console_instance;
    console = &console_instance;
    console->setParent(&entry);

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
