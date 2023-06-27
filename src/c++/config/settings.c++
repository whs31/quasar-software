#include "settings.h"

namespace Config
{
  internal::SettingsWrapper::SettingsWrapper(QObject* parent)
      : QObject(parent)
  {}

  QVariant internal::SettingsWrapper::parameter(const QString& key) const noexcept
  {
    if(not m_json.count(key))
      return "INVALID";
    return m_json.at(key);
  }

  void internal::SettingsWrapper::load() noexcept
  {
    // todo
  }

  void internal::SettingsWrapper::save() noexcept
  {
    // todo
  }

  void internal::SettingsWrapper::set(const QString& key, const QVariant& value) noexcept
  {
    if(m_json.count(key))
      m_json[key] = value;
    else
      m_json.insert({key, value});
  }

  Settings* Settings::get() { static Settings instance; return &instance; }

  void Settings::setParameter(const QString& key, const QVariant& value) noexcept
  {
    m_wrapper->set(key, value);
  }

  void Settings::save() noexcept
  {
    // todo
  }

  void Settings::revert() noexcept
  {
    // todo
  }

  QVariant Settings::parameter(const QString& key) const
  {
    return m_wrapper->parameter(key);
  }

  Settings::Settings(QObject* parent)
      : QObject(parent)
      , m_wrapper(new internal::SettingsWrapper(this))
  {
    this->revert();
  }
} // Config