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

  qDebug() << "Waiting for app to close...";
  std::this_thread::sleep_for(std::chrono::seconds(3));

  qDebug() << "Checking if file downloaded correctly...";
  if(not source.exists())
  {
    qCritical() << "Source file is missing";
    std::cout << "Press any key to exit...";
    std::cin.get();
    return 1;
  }

  qDebug() << "Checking previous executable...";
  if(QFile::exists(QCoreApplication::applicationDirPath() + "/QuaSAR.exe"))
  {
    qDebug() << "Deleting previous executable...";
    QFile::remove(QCoreApplication::applicationDirPath() + "/QuaSAR.exe");
  }

  qDebug() << "Copying...";
  bool res = source.copy(QCoreApplication::applicationDirPath() + "/QuaSAR.exe");
  if(not res)
  {
    qCritical() << "Failed to copy";
    std::cout << "Press any key to exit...";
    std::cin.get();
    return 1;
  }

  qDebug() << "Cleaning up...";
  source.remove();

  qDebug() << "Removing old configs...";
  QFile::remove(QCoreApplication::applicationDirPath() + "/config/constants.json");
  QFile::remove(QCoreApplication::applicationDirPath() + "/config/network.json");

  qDebug() << "Success!";
  std::cout << "Press any key to exit...";
  std::cin.get();

  return 0;
}
