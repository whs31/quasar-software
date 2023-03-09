//  https://github.com/noxware/qt-quick-flickable-and-zoomable-by-mouse-image-example
//  вот тут написано как сделать херню которую я хочу

#include <QApplication>
#include "coreui.h"
#if defined(Q_OS_WIN)
#include <windows.h>
#endif

QString logName = "";
bool m_pointer_reset_flag = false;
QScopedPointer<CoreUI> core;

void debugLogger(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    int msgt = 0;
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg(msg);
        msgt = 0;
        break;
    case QtWarningMsg:
        txt = QString("%1").arg(msg);
        msgt = 2;
    break;
    case QtInfoMsg:
        txt = QString("%1").arg(msg);
        msgt = 1;
    break;
    case QtCriticalMsg:
        txt = QString("%1").arg(msg);
        msgt = 3;
    break;
    case QtFatalMsg:
        txt = QString("%1").arg(msg);
        msgt = 4;
    break;
    }

    QFile outFile(CacheManager::getSettingsPath() + "/logs/" + logName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << '\n';
    if(m_pointer_reset_flag)
        core.get()->debugStreamUpdate(txt, msgt);
}

int main(int argc, char *argv[]) {
    #if defined(Q_OS_WIN)
        FreeConsole();
    #endif
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    QApplication app(argc, argv);
    qSetMessagePattern("[%{time process}] %{message}");

    QQuickStyle::setStyle("Material");

    #include <QDateTime>
    QDateTime date = QDateTime::currentDateTime();
    logName = date.toString("dd.MM.yyyy-hh:mm");
    logName.prepend("log-");
    logName.append(".txt");
    core.reset(new CoreUI());
    m_pointer_reset_flag = true;
    qInstallMessageHandler(debugLogger);
    core.get()->show();
    core.get()->showMaximized();
    //window.showFullScreen();
    return app.exec();
}
