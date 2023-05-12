#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace Config
{
    class Paths : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(Paths)

        public:
            __exposed static QString root();
            __exposed static QString imageCache();
            __exposed static QString mapConfig();
            __exposed static QString plugins();
            __exposed static QString config();
            __exposed static QString logs();
            __exposed static QString themes();

            __exposed void createImageCache(void);
            __exposed void clearImageCache(void);

        private:
            explicit Paths(QObject* parent = nullptr);
            void createMapConfigs(void);
    };
} // namespace Config;
