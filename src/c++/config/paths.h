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

        //! @var Constant for defining how many LOD folders
        //!      will be created in cache.
        constexpr static const int LOD_LEVELS = 2;

        public:
            //! @brief   Returns singleton instance of class.
            static Paths* get();

            //! @brief   Returns application root directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString root();

            //! @brief   Returns cache directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString imageCache();

            //! @brief   Returns specified LOD directory.
            //! @param   level - specified LOD level for directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString lod(int level);

            //! @brief   Returns TCP-IP cache directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString tcp();

            //! @brief   Returns osmconfigs directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString mapConfig();

            //! @brief   Returns offline tiles directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString offlineTiles();

            //! @brief   Returns config directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString config();

            //! @brief   Returns logs and route-logs directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString logs();

            //! @brief   Returns themes directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString themes();

            //! @brief   Returns bash-scripts directory.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString bash();

            //! @brief   Returns directory for runtime-evaluated bash scripts.
            //! @details Can be invoked from QML.
            Q_INVOKABLE [[nodiscard]] static QString runtimeBash();


            //! @brief   Creates and setups image cache.
            //! @details Can be invoked from QML.
            Q_INVOKABLE void createImageCache(void) noexcept;

            //! @brief   Erases image and TCP-IP cache from disk.
            //! @details Can be invoked from QML.
            Q_INVOKABLE void clearImageCache(void) noexcept;

        private:
            explicit Paths(QObject* parent = nullptr);
            Paths(const Paths&);
            Paths &operator=(const Paths&);

            void createMapConfigs(void);
    };
} // namespace Config;
