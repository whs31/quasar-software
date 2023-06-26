#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
//  #if defined(Q_OS_WIN)
//  FreeConsole();
//  #endif

  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setOrganizationName(PROJECT_COMPANY);

  QString source_file_path = QCoreApplication::applicationDirPath() + "/cache/QuaSAR.exe";
  QFile source(source_file_path);

  if(not source.exists())
  {
    qCritical() << "Source file is missing";
    return 1;
  }

  bool res = source.copy(QCoreApplication::applicationDirPath() + "QuaSAR.exe");
  if(not res)
  {
    qCritical() << "Failed to copy";
    return 1;
  }

  source.remove();
  return 0;
}