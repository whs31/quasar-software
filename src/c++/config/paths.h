#pragma once

#include <QtCore/QObject>

namespace Config
{
  //! @brief Class, providing access to commonly
  //!        used filesystem paths and resource
  //!        management.
  class Paths : public QObject
  {
    Q_OBJECT

      constexpr static const int LOD_LEVELS = 2;

    public:
      //! @brief   Returns singleton instance of class.
      static Paths* get();

      //! @brief   Returns application root directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString root();

      //! @brief   Returns cache directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString imageCache();

      //! @brief   Returns specified LOD directory.
      //! @param   level - specified LOD level for directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString lod(int level);

      //! @brief   Returns TCP-IP cache directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString tcp();

      //! @brief   Returns osmconfigs directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString mapConfig();

      //! @brief   Returns offline tiles directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString offlineTiles();

      //! @brief   Returns config directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString config();

      //! @brief   Returns logs and route-logs directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString logs();

      //! @brief   Returns themes directory.
      //! @note Can be invoked from QML.
      Q_INVOKABLE [[nodiscard]] static QString themes();

      //! @brief   Creates and setups image cache.
      //! @note Can be invoked from QML.
      Q_INVOKABLE void createImageCache() noexcept;

      //! @brief   Erases image and TCP-IP cache from disk.
      //! @note Can be invoked from QML.
      Q_INVOKABLE void clearImageCache() noexcept;

    private:
      explicit Paths(QObject* parent = nullptr);
      Paths(const Paths&);
      Paths &operator=(const Paths&);

      void createMapConfigs() noexcept;
  };
} // namespace Config;
