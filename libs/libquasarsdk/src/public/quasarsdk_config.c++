//
// Created by whs31 on 05.07.23.
//

#include "quasarsdk_config.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>

inline void initialize_qrc_file_within_namespace() { Q_INIT_RESOURCE(quasarsdk); }

namespace QuasarSDK
{
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