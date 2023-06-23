#include "colortheme.h"
#include "config/config.h"

namespace GUI
{
  internal::ColorThemeWrapper::ColorThemeWrapper(QObject* parent)
    : QObject(parent)
  {}

  QString internal::ColorThemeWrapper::color(internal::ColorThemeWrapper::Color key) const noexcept
  {
    if(m_activeTheme.empty())
      return "red";
    if(not m_activeTheme.count(key))
      return "purple";
    return m_activeTheme.at(key);
  }

  void internal::ColorThemeWrapper::set(const std::map<Color, QString>& theme_dict) noexcept
  {
    m_activeTheme = theme_dict;
  }

  ColorTheme::ColorTheme(QObject* parent)
    : QObject(parent)
    , m_wrapper(new internal::ColorThemeWrapper(this))
  {
  // todo scan for themes, fill theme list, set active theme, set map
}

  void ColorTheme::set(const std::map<internal::ColorThemeWrapper::Color, QString>& dict) noexcept
  {
    m_wrapper->set(dict);
    emit activeChanged();
  }

  QString ColorTheme::activeThemeName() const { return m_activeThemeName; }
  void ColorTheme::setActiveThemeName(const QString& other)
  {
    if(other == m_activeThemeName)
      return;
    m_activeThemeName = other;
    emit activeThemeNameChanged();
  }
} // GUI