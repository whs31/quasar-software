#include <QWidget>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include <qqml.h>
#include <QStandardPaths>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "coreui.h"
#include "style.h"

#include "smath.h"
#include "backend/fmousekeyhandler.h"


void debugLogger(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    int msgt = 0;
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg(msg+"\r\n");
        msgt = 0;
        break;
    case QtWarningMsg:
        txt = QString("%1").arg(msg+"\r\n");
        msgt = 2;
    break;
    case QtInfoMsg:
        txt = QString("%1").arg(msg+"\r\n");
        msgt = 1;
    break;
    case QtCriticalMsg:
        txt = QString("%1").arg(msg+"\r\n");
        msgt = 3;
    break;
    case QtFatalMsg:
        txt = QString("%1").arg(msg+"\r\n");
        msgt = 4;
    break;
    }
    QFile outFile(CacheManager::getSettingsPath() + "/log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << '\n';
    CoreUI* pointer = CoreUI::getDebugPointer();
    if(pointer->getReady())
    {
        pointer->debugStreamUpdate(txt, msgt);
    }
}

int main(int argc, char *argv[]) {
    qmlRegisterType<SMath>("SMath", 1, 0, "SMath");
    qmlRegisterType<FMouseKeyHandler>("MouseKeyHandler", 1, 0, "MouseKeyHandler");
    QApplication app(argc, argv);
    
    //cache setup
    CacheManager::initializeCache();

    QQuickStyle::setStyle("Material");  //графика для QML
    new Style(false);                   //false при сборке релиза
    new TilesManager();

    qInstallMessageHandler(debugLogger);
    CoreUI window;

    window.show();
    window.showMaximized();
    return app.exec();
}