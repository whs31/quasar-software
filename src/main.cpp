#include <QWidget>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include <qqml.h>
#include <QStandardPaths>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "mainwindow.h"
#include "ui_mainwindow.h"
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
        txt = QString(">: %1").arg(msg+"\r\n");
        msgt = 2;
    break;
    case QtInfoMsg:
        txt = QString(">: %1").arg(msg+"\r\n");
        msgt = 1;
    break;
    case QtCriticalMsg:
        txt = QString(">: %1").arg(msg+"\r\n");
        msgt = 3;
    break;
    case QtFatalMsg:
        txt = QString(">: %1").arg(msg+"\r\n");
        msgt = 4;
    break;
    }
    QFile outFile(QCoreApplication::applicationDirPath()+"/debug_log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    MainWindow* pointer = MainWindow::getDebugPointer();
    pointer->debugStreamUpdate(txt, msgt);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qInstallMessageHandler(debugLogger);
    QFile qss(":/stylesheet/stylesheet.qss");
    if (!qss.exists())   {
        printf("[MAINTHREAD] Unable to set stylesheet, file not found\n");
    }
    else   {
        qss.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qss);
        qApp->setStyleSheet(ts.readAll());                          //графика для Widgets
    }
    QQuickStyle::setStyle("Material");                              //графика для QML
    MainWindow window;

    window.show();
    window.showMaximized();

    //qDebug()<<QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation); //здесь валяется кэш карт

    return app.exec();
}

__attribute__((constructor)) void showVersion() {
    //qInfo() << PROJECT_NAME << "version" << PROJECT_VERSION << "source" << PROJECT_SOURCE_DATE << "build" << PROJECT_BUILD_DATE << "start" << QDateTime::currentDateTimeUtc().toString("dd.MM.yyyy hh:mm:ss").toStdString().data();
}
