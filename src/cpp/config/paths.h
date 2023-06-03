#pragma once

#include <QtCore/QObject>
#include <LPVL/Global>

namespace Config
{
    class Paths : public QObject
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(Paths)

        constexpr static const int LOD_LEVELS = 2;

        public:
            Q_INVOKABLE static QString root();
            Q_INVOKABLE static QString imageCache();
            Q_INVOKABLE static QString lod(int level);
            Q_INVOKABLE static QString tcp();
            Q_INVOKABLE static QString mapConfig();
            Q_INVOKABLE static QString offlineTiles();
            Q_INVOKABLE static QString plugins();
            Q_INVOKABLE static QString config();
            Q_INVOKABLE static QString logs();
            Q_INVOKABLE static QString themes();

            Q_INVOKABLE void createImageCache(void);
            Q_INVOKABLE void clearImageCache(void);

        private:
            explicit Paths(QObject* parent = nullptr);
            void createMapConfigs(void);
    };
} // namespace Config;
