#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace Config
{
    class Paths : public QObject
    {
        Q_OBJECT
        DECLARE_SINGLETON(Paths)

        public:
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
