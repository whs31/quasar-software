#pragma once

#include <QtCore/QObject>
#include "definitions.h++"

namespace Config
{
    class Paths : public QObject
    {
        Q_OBJECT

        static Paths* instance;

        public:
            static Paths* get(QObject* parent = nullptr);

            __qml static QString root();
            __qml static QString imageCache();
            __qml static QString mapConfig();
            __qml static QString plugins();
            __qml static QString config();
            __qml static QString logs();
            __qml static QString themes();

            __qml void createImageCache(void);
            __qml void clearImageCache(void);

        private:
            explicit Paths(QObject* parent = nullptr);
            void createMapConfigs(void);
    };
} // namespace Config;
