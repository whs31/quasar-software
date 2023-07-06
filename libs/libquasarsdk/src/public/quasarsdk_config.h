/**
 *  \file quasarsdk_config.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QMutex>

namespace QuasarSDK
{
  class Config
  {
    public:
      static Config* get();

      template<typename T>
      T value(const QString& key);

    private:
      Config();
      Config(const Config&);
      Config& operator=(const Config&);

    private:
      QMap<QString, QVariant> m_values;
  };

  template<typename T>
  T Config::value(const QString &key)
  {
    static QMutex mutex;
    mutex.lock();
    auto ret = m_values.value(key).value<T>();
    mutex.unlock();
    return ret;
  }
} // QuasarSDK