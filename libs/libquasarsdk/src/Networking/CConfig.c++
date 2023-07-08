/** \class QuasarSDK::Config CConfig.h <QuasarSDK/Networking/CConfig.h>
  * \tableofcontents
  * \brief Синглтон, отвечающий за индивидуальные настройки библиотеки во времени выполнения.
  * \details Предоставляет функционал чтения и записи <tt>.json</tt> файла с настройками,
  * связанными с обработкой изображений и сетевой частью комплекта разработчика РЛС "Квазар".
  *
  * Настройки сохраняются по пути: <tt>./config/sdk-config.json</tt>.
  * Если файл с настройками не существует, то будет создан новый файл, который
  * будет содержать настройки по умолчанию.
  *
  * Файл с настройками можно редактировать вручную, как во время выполнения программы,
  * так и при закрытом приложении. Некоторые настройки не будут изменены во время выполнения,
  * пока программа не будет перезапущена.
  *
  * Полный список настроек приведен ниже:
  * \code {.js}
    {
     "EXECD_FORM_TELESCOPIC": "$telescopic",
     "EXECD_FORM_STRIP_DEBUG": "$strip",
     "EXECD_FORM_STRIP_START": "$strip_start",
     "EXECD_FORM_STRIP_STOP": "$strip_stop",
     "EXECD_FOCUS_TELESCOPIC": "$focus",
     "EXECD_STORAGE_FETCH": "$storage_status()",
     "EXECD_STORAGE_CLEAR": "$clear_storage()",
     "EXECD_REBOOT": "$reboot()",
     "EXECD_POWEROFF": "$poweroff()",

     "STDOUT_STORAGE_STATUS": "*FREE_DISK_SPACE*",

     "TCP_SERVER_TIMEOUT": "10000",

     "PROCESSING_CONCURRENCY_THREADS_STRIP": "4",
     "PROCESSING_CONCURRENCY_THREADS_TELESCOPIC": "2",
     "PROCESSING_DEBUG_PRESERVE_BINARY": "false",
     "PROCESSING_DEBUG_SAVE_STRIP_MATRIX": "false",
     "PROCESSING_IMAGE_INITIAL_OPACITY": "1",
     "PROCESSING_IMAGE_INITIAL_VISIBILITY": "true",
     "PROCESSING_STRIP_PACKAGE_MAX_SIZE": "1024",

     "NETWORK_DELAY_THRESHOLD_DISCONNECT": "10.0"
    }
  * \endcode
  */

#include "CConfig.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>

inline void initialize_qrc_file_within_namespace() { Q_INIT_RESOURCE(quasarsdk); }

namespace QuasarSDK
{
  /**
   * \brief Возвращает указатель на уникальный объект класса.
   * \return Указатель на объект.
   */
  Config* Config::get() { static Config instance; return &instance; }

  Config::Config()
  {
    initialize_qrc_file_within_namespace();
    const QString CONFIG_PATH = QCoreApplication::applicationDirPath() + "/config";
    QDir config_directory(CONFIG_PATH);
    if(not config_directory.exists())
      config_directory.mkpath(CONFIG_PATH);
    QFile file(CONFIG_PATH + "/sdk-config.json");
    if(not file.exists())
      QFile::copy(":/quasarsdk/rc/sdk-config.json", CONFIG_PATH + "/sdk-config.json");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray jsonData = file.readAll();
      file.close();

      QJsonDocument doc = QJsonDocument::fromJson(jsonData);
      if(not doc.isNull() and doc.isObject())
      {
        QJsonObject json = doc.object();
        for(auto it = json.begin(); it != json.end(); ++it)
          m_values.insert(it.key(), it.value().toVariant());
      }
    }
  }
} // QuasarSDK