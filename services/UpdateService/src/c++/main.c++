#include <iostream>
#include <thread>
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

  std::this_thread::sleep_for(std::chrono::seconds(3));

  if(not source.exists())
  {
    qCritical() << "Source file is missing";
    std::cout << "Press any key to exit...";
    std::cin.get();
    return 1;
  }

  bool res = source.copy(QCoreApplication::applicationDirPath() + "/QuaSAR.exe");
  if(not res)
  {
    qCritical() << "Failed to copy";
    std::cout << "Press any key to exit...";
    std::cin.get();
    return 1;
  }

  source.remove();

  QFile::remove(QCoreApplication::applicationDirPath() + "/config/constants.json");
  QFile::remove(QCoreApplication::applicationDirPath() + "/config/network.json");

  std::cout << "Press any key to exit...";
  std::cin.get();

  return 0;
}
