#include "settings.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "config/paths.h"

namespace Config
{
  internal::SettingsWrapper::SettingsWrapper(QObject* parent)
      : QObject(parent)
  {
    qRegisterMetaType<internal::SettingsWrapper*>("internal::SettingsWrapper*");
  }

  QVariant internal::SettingsWrapper::parameter(const QString& key) const noexcept
  {
    if(not m_json.count(key))
      return "INVALID";
    return m_json.at(key);
  }

  void internal::SettingsWrapper::load() noexcept
  {
    qInfo() << "$ [SETTINGS] Loading settings";
    QFile file(Config::Paths::config() + "/settings.json");
    if(not file.exists())
      QFile::copy(":/json/settings.json", Config::Paths::config() + "/settings.json");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QByteArray jsonData = file.readAll();
      file.close();

      QJsonDocument doc = QJsonDocument::fromJson(jsonData);
      if(not doc.isNull() and doc.isObject())
      {
        QJsonObject json = doc.object();
        for(auto it = json.begin(); it != json.end(); ++it)
          m_json.insert({it.key(), it.value().toVariant()});
      }
    }
  }

  void internal::SettingsWrapper::save() noexcept
  {
    qInfo() << "$ [SETTINGS] Saving settings";
    QByteArray data_to_save = QJsonDocument(QJsonObject::fromVariantMap(QMap<QString, QVariant>(m_json))).toJson();
    QFile::remove(Config::Paths::config() + "/settings.json");
    QFile file(Config::Paths::config() + "/settings.json");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      file.write(data_to_save);
      file.close();
    }
  }

  void internal::SettingsWrapper::set(const QString& key, const QVariant& value) noexcept
  {
    if(m_json.count(key))
      m_json[key] = value;
    else
      m_json.insert({key, value});
  }

  Settings* Settings::get() { static Settings instance; return &instance; }
  Settings::Settings(QObject* parent)
    : QObject(parent)
    , m_wrapper(new internal::SettingsWrapper(this))
  {
    this->load();
  }

  void Settings::save() noexcept { m_wrapper->save(); }
  void Settings::revert() noexcept { m_wrapper->load(); emit ioChanged(); }
  void Settings::load() noexcept { this->revert(); }
  QVariant Settings::parameter(const QString& key) const { return m_wrapper->parameter(key); }
  void Settings::setParameter(const QString& key, const QVariant& value) noexcept
  {
    m_wrapper->set(key, value);
    if(key == "application/theme")
      emit themeChanged();
  }

  QString Settings::projectVersion() { return PROJECT_VERSION; }
} // Config