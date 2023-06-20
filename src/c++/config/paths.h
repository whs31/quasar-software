#pragma once

#include <QtCore/QObject>

//! @namespace Namespace for working with data,
//!            which is shared between sessions.
namespace Config
{
    //! @class Class, providing access to commonly
    //!        used filesystem paths and resource
    //!        management.
    class Paths : public QObject
    {
        Q_OBJECT

        //! @var Constant for defining, how many LOD folders
        //!      will be created in cache.
        constexpr static const int LOD_LEVELS = 2;

        public:
            //! @brief Returns singleton instance of class.
            static Paths *get() { static Paths instance; return &instance; }

            Q_INVOKABLE static QString root();          //! @brief Returns application root directory.
            Q_INVOKABLE static QString imageCache();    //! @brief Returns cache directory.
            Q_INVOKABLE static QString lod(int level);  //! @brief Returns specified LOD directory.
            Q_INVOKABLE static QString tcp();           //! @brief Returns TCP-IP cache directory.
            Q_INVOKABLE static QString mapConfig();     //! @brief Returns osmconfigs directory.
            Q_INVOKABLE static QString offlineTiles();  //! @brief Returns offline tiles directory.
            Q_INVOKABLE static QString config();        //! @brief Returns config directory.
            Q_INVOKABLE static QString logs();          //! @brief Returns logs and route-logs directory.
            Q_INVOKABLE static QString themes();        //! @brief Returns themes directory.
            Q_INVOKABLE static QString bash();          //! @brief Returns bash-scripts directory.
            Q_INVOKABLE static QString runtimeBash();   //! @brief Returns directory for runtime-evaluated bash scripts.

            //! @brief Creates and setups image cache.
            Q_INVOKABLE void createImageCache(void);

            //! @brief Erases image and TCP-IP cache from disk.
            Q_INVOKABLE void clearImageCache(void);

        private:
            explicit Paths(QObject* parent = nullptr);
            Paths(const Paths&);
            Paths &operator=(const Paths&);
            void createMapConfigs(void);
    };
} // namespace Config;
