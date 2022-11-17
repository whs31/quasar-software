#include <QWidget>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include <qqml.h>
#include <QStandardPaths>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile qss(":/stylesheet/stylesheet.qss");
    if (!qss.exists())   {
        printf("Unable to set stylesheet, file not found\n");
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
