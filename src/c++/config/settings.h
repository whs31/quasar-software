#pragma once

#include <map>
#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Config::internal
{
  class SettingsWrapper : public QObject
  {
    Q_OBJECT

    public:
      explicit SettingsWrapper(QObject* parent = nullptr);

      [[nodiscard]] Q_INVOKABLE QVariant parameter(const QString& key) const noexcept;
      void set(const QString& key, const QVariant& value) noexcept;

      void load() noexcept;
      void save() noexcept;

    private:
      std::map<QString, QVariant> m_json;
  };
} // GUI

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(Config::internal::SettingsWrapper*)

namespace Config
{
  class Settings : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(internal::SettingsWrapper* io MEMBER m_wrapper NOTIFY ioChanged) // re-evaluate binding by this trick
    Q_PROPERTY(QString projectVersion READ projectVersion CONSTANT)

    public:
      static Settings* get();
      ~Settings() override = default;

      Q_INVOKABLE void setParameter(const QString& key, const QVariant& value) noexcept;
      Q_INVOKABLE void save() noexcept;
      Q_INVOKABLE void revert() noexcept;
      Q_INVOKABLE void load() noexcept;

      [[nodiscard]] QVariant parameter(const QString& key) const;

      template<typename T>
      [[nodiscard]] T value(const QString& key) const { return parameter(key).value<T>(); }

      [[nodiscard]] static QString projectVersion() ;

    signals:
      void ioChanged();
      void themeChanged();
      void compatibilityChanged();

    private:
      explicit Settings(QObject* parent = nullptr);
      Settings(const Settings&);
      Settings& operator=(const Settings&);

    private:
      internal::SettingsWrapper* m_wrapper;
  };
} // Config
