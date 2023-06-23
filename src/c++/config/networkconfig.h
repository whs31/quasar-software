#pragma once

#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QMutex>

#define NETCFG Config::NetworkConfig::get()->def

namespace Config
{
  class NetworkConfig
  {
    public:
      static NetworkConfig* get();

      template<typename T = QString>
      T def(const QString& key);

    private:
      NetworkConfig();
      NetworkConfig(const NetworkConfig&);
      NetworkConfig& operator=(const NetworkConfig&);

    private:
      QMap<QString, QVariant> m_values;
  };

  template<typename T>
  T NetworkConfig::def(const QString &key)
  {
    static QMutex mutex;
    mutex.lock();
    auto ret = m_values.value(key).value<T>();
    mutex.unlock();
    return ret;
  }
} // Config
