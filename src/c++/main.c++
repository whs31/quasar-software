#include "quasar.h"
#include <QtWidgets/QApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>
#include <argparse.h>
#include "gui/terminal/debugconsole.h"

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

CONSOLE_INIT_HANDLER

static const char* const usages[] =
{
  "basic [options] [[--] args]",
  "basic [options]",
  nullptr,
};

int main(int argc, char* argv[])
{
  #if defined(Q_OS_WIN)
  FreeConsole();
  #endif

  QApplication app(argc, argv);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setApplicationVersion(PROJECT_VERSION);
  QCoreApplication::setOrganizationName(PROJECT_COMPANY);
  #ifndef Q_OS_WIN
  app.setWindowIcon(QIcon(":/icon.png"));
  #else
  app.setWindowIcon(QIcon(":/icon.ico"));
  #endif

  int no_console = 0;
  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_GROUP("Basic options"),
    OPT_BOOLEAN(0, "no-log-redirect", &no_console, "disable internal console and log into external terminal", nullptr, 0, 0),
    OPT_END(),
  };
  struct argparse argparse;
  argparse_init(&argparse, options, usages, 0);
  argparse_describe(&argparse, "\nQuaSAR SAR control software.", "\n(c) 2023 Radar-MMS");
  argc = argparse_parse(&argparse, argc, (const char**)argv);

  if(not no_console)
    qInstallMessageHandler(CONSOLE_HANDLER);
  qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

  const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
  qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
  QQuickStyle::setStyle("Material");

  QuaSAR quasar;

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
    qCritical() << "[QML FAILURE] " << component.errorString();
  }

  return app.exec();
}
