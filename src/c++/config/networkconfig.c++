#include "networkconfig.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "config/paths.h"

namespace Config
{

  NetworkConfig *NetworkConfig::get() { static NetworkConfig instance; return &instance; }

  NetworkConfig::NetworkConfig()
  {
    QFile file(Config::Paths::config() + "/network.json");
    if(not file.exists())
      QFile::copy(":/json/network.json", Config::Paths::config() + "/network.json");

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

} // Config