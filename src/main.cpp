#include <QApplication>
#include "coreui.h"

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
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    QApplication app(argc, argv);

    QQuickStyle::setStyle("Material");                      //графика для QML
    qInstallMessageHandler(debugLogger);
    CoreUI window;
    window.showFullScreen();
    return app.exec();
}
