#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtQml/QQmlPropertyMap>
#include "definitions.h++"

class QSettings;

namespace Config
{
    class Config : public QObject
    {
        Q_OBJECT

        static Config* instance;
        const QMap<QString, QVariant> defaults = {
            {"network_remoteIP", "127.0.0.1"}
        };
        QQmlPropertyMap m_values;
        QSettings* ini;

        public:
            static Config* get(QObject* parent = nullptr);
            virtual ~Config() = default;
            __qml QQmlPropertyMap* map();

            void sync();
            void save();
            void load();
            void revert();
            void reset();

            signals:

        private:
            explicit Config(QObject *parent = nullptr);
    };
} // namespace Config;
