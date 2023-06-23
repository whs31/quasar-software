#pragma once

#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QMutex>

#define ICFG Config::InternalConfig::get()->def

namespace Config
{
  class InternalConfig
  {
    public:
      //! @brief Возвращает указатель на статический экземпляр класса.
      static InternalConfig* get();

      template<typename T>
      T def(const QString& key);

    private:
      InternalConfig();
      InternalConfig(const InternalConfig &);
      InternalConfig &operator=(const InternalConfig &);

    private:
      QMap<QString, QVariant> m_values;
  };

  template<typename T>
  T InternalConfig::def(const QString &key)
  {
    static QMutex mutex;
    mutex.lock();
    auto ret = m_values.value(key).value<T>();
    mutex.unlock();
    return ret;
  }
} // Config
