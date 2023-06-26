#include "entry.h"
#include <QtWidgets/QApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
  #if defined(Q_OS_WIN)
  FreeConsole();
  #endif

  QApplication app(argc, argv);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setApplicationVersion(PROJECT_VERSION);
  QCoreApplication::setOrganizationName(PROJECT_COMPANY);

  qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

  const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
  qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
  QQuickStyle::setStyle("Material");

  Entry entry;

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