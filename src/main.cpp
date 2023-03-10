//  https://github.com/noxware/qt-quick-flickable-and-zoomable-by-mouse-image-example
//  вот тут написано как сделать херню которую я хочу

#include <QApplication>
#include "coreui.h"
#include <QList>
#include <QPair>
#if defined(Q_OS_WIN)
#include <windows.h>
#endif




//! @brief Логгер для кастомной имплементации консоли отладки.
//! @details Сохраняет логи в отдельный файл, перенаправляет их в консоль отладки
//!          и задает цвет для разных типов сообщений.
QString logName = "";
QScopedPointer<CoreUI> core;
QList<QPair<int, QString>> cachedDebugInfo;
bool releaseCacheFlag = false;
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
    if(core.get() != nullptr)
    {
        core.get()->debugStreamUpdate(txt, msgt);
        if(not releaseCacheFlag)
            for (QPair<int, QString> message : cachedDebugInfo) {
                core.get()->debugStreamUpdate(message.second, message.first);
            }
    }
    else
        cachedDebugInfo.append(QPair<int, QString>(msgt, txt));
}

int main(int argc, char *argv[]) {
    #if defined(Q_OS_WIN)
        FreeConsole();
    #endif
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    QApplication app(argc, argv);
    qSetMessagePattern("[%{time process}] %{message}");

    #include <QDateTime>
    QDateTime date = QDateTime::currentDateTime();
    logName = date.toString("dd.MM.yyyy-hh:mm");
    logName.prepend("log-");
    logName.append(".txt");
    qInstallMessageHandler(debugLogger);
    core.reset(new CoreUI());
    core.get()->show();
    core.get()->showFullScreen();
    return app.exec();
}
