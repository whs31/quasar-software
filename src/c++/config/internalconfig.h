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
            QMap<QString, QVariant> m_defaults = {
                {"PROCESSING_CONCURRENCY_THREADS_TELESCOPIC", "2"},
                {"PROCESSING_CONCURRENCY_THREADS_STRIP", "4"},
                {"PROCESSING_IMAGE_INITIAL_VISIBILITY", "true"},
                {"PROCESSING_IMAGE_INITIAL_OPACITY", "1"},
                {"PROCESSING_DEBUG_SAVE_STRIP_MATRIX", "true"},
                {"PROCESSING_DEBUG_SHOW_STRIP_WINDOW", "true"},
                {"PROCESSING_DEBUG_PRESERVE_BINARY", "false"},
                {"PROCESSING_STRIP_PACKAGE_MAX_SIZE", "1024"}
            };
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
