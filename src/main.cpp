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
    QApplication app(argc, argv);

    
    QQuickStyle::setStyle("Material");                      //графика для QML
    qInstallMessageHandler(debugLogger);

    CoreUI window;

	// QFontDatabase::addApplicationFont("qrc:/ui-resources/fonts/proximanova_regular.ttf");
	// QFontDatabase::addApplicationFont("qrc:/ui-resources/fonts/HelveticaNeueCyr-Light.ttf");
	// QFont proximaNova = QFont("Proxima Nova", 10, 1);
	// QFont helveticaNeue = QFont("Helvetica Neue Embedded", 10, 1);

    window.show();
    window.showMaximized();
    return app.exec();
}
