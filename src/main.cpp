#include <QApplication>
#include "coreui.h"
#if defined(Q_OS_WIN)
#include <windows.h>
#endif

QString logName = "";

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

    QFile outFile(CacheManager::getSettingsPath() + "/logs/" + logName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << '\n';
    CoreUI* pointer = CoreUI::getDebugPointer();
    if(pointer->getReady())
        if(!txt.contains("QDeclarativeGeoMap_QML_73") && !txt.contains("all providers resolved"))
            pointer->debugStreamUpdate(txt, msgt);
}

int main(int argc, char *argv[]) {
    #if defined(Q_OS_WIN)
        FreeConsole();
    #endif
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    QApplication app(argc, argv);

    QQuickStyle::setStyle("Material");                      //графика для QML

    #include <QDateTime>
    QDateTime date = QDateTime::currentDateTime();
    logName = date.toString("dd.MM.yyyy-hh:mm");
    logName.prepend("log-");
    logName.append(".txt");
    qInstallMessageHandler(debugLogger);
    CoreUI window;
    window.show();
    window.showFullScreen();
    return app.exec();
}
