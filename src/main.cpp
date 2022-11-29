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
    QFile outFile(QCoreApplication::applicationDirPath()+"/debug_log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << '\n';
    CoreUI* pointer = CoreUI::getDebugPointer();
    pointer->debugStreamUpdate(txt, msgt);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qInstallMessageHandler(debugLogger);
    QQuickStyle::setStyle("Material");                              //графика для QML
    new Style(false);  //false при сборке релиза
    CoreUI window;

    window.show();
    window.showMaximized();
    return app.exec();
}

__attribute__((constructor)) void showVersion() {
    //qInfo() << PROJECT_NAME << "version" << PROJECT_VERSION << "source" << PROJECT_SOURCE_DATE << "build" << PROJECT_BUILD_DATE << "start" << QDateTime::currentDateTimeUtc().toString("dd.MM.yyyy hh:mm:ss").toStdString().data();
}
