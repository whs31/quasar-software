/**
 * \defgroup legacy Классы и функции, не рекомендуемые к использованию.
 * Группа классов, которые не используются в текущей кодовой базе, однако,
 * остаются в ней по тем или иным причинам.
 *
 * **Крайне не рекомендуется использовать сущности из этого списка в новом коде.**
 *
 * \namespace Scenegraph
 * \brief Пространство имен для библиотеки Scenegraph.
 *
 * \namespace Scenegraph::Utils
 * \brief Пространство имен для вспомогательных классов и функций, связанных с QML Scenegraph.
 */

#include "CColorProvider.h"
#include <random>

int random_in_range(int min, int max)
{
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> dist(min, max); // define the range

  return dist(gen);
}

namespace Scenegraph::Utils
{
  ColorProvider::ColorProvider(QObject* parent)
    : QObject(parent)
    , m_it({0, 0})
    , m_currentTheme(Light)
    , m_currentBehavior(RandomCycle)
    , m_dark_palette({
      {Rosewater, QColor(245, 224, 220)},
      {Flamingo, QColor(242, 205, 205)},
      {Pink, QColor(245, 194, 231)},
      {Mauve, QColor(203, 166, 247)},
      {Red, QColor(243, 139, 168)},
      {Maroon, QColor(235, 160, 172)},
      {Peach, QColor(250, 179, 135)},
      {Yellow, QColor(249, 226, 175)},
      {Green, QColor(166, 227, 161)},
      {Teal, QColor(148, 226, 213)},
      {Sky, QColor(137, 220, 235)},
      {Sapphire, QColor(116, 199, 236)},
      {Blue, QColor(137, 180, 250)},
      {Lavender, QColor(180, 190, 254)},
    })
    , m_light_palette({
      {Rosewater, QColor(220, 138, 120)},
      {Flamingo, QColor(221, 120, 120)},
      {Pink, QColor(234, 118, 203)},
      {Mauve, QColor(136, 57, 239)},
      {Red, QColor(210, 15, 57)},
      {Maroon, QColor(230, 69, 83)},
      {Peach, QColor(254, 100, 11)},
      {Yellow, QColor(223, 142, 29)},
      {Green, QColor(64, 160, 43)},
      {Teal, QColor(23, 146, 153)},
      {Sky, QColor(4, 165, 229)},
      {Sapphire, QColor(32, 159, 181)},
      {Blue, QColor(30, 102, 245)},
      {Lavender, QColor(114, 135, 253)},
    })
    , m_exclude_list({false})
  {
    for(auto& state : m_exclude_list)
      state = false;
  }

  QString ColorProvider::next() const
  {
    QString ret;
    switch(m_currentBehavior)
    {
      case OrderedCycle: {
        switch(m_currentTheme)
        {
          case Light: ret = m_light_palette.at((BaseColor)m_it.count).name(); break;
          case Dark: ret = m_dark_palette.at((BaseColor)m_it.count).name(); break;
        }

        ++m_it.count;
        if(m_it.count > Max) {
          m_it.count = Min;
          ++m_it.loop;
        }
        break;
      }
      case RandomCycle: {
        int current_idx = random_in_range(Min, Max);

        switch(m_currentTheme)
        {
          case Light: ret = m_light_palette.at((BaseColor)current_idx).name(); break;
          case Dark: ret = m_dark_palette.at((BaseColor)current_idx).name(); break;
        }

        ++m_it.count;
        if(m_it.count > Max) {
          m_it.count = Min;
          ++m_it.loop;
        }
        break;
      }
      case OrderedTint: {
        switch(m_currentTheme)
        {
          case Light: ret = m_light_palette.at((BaseColor)m_it.count).lighter(100 + m_it.loop * 10).name(); break;
          case Dark: ret = m_dark_palette.at((BaseColor)m_it.count).darker(100 + m_it.loop * 10).name(); break;
        }

        ++m_it.count;
        if(m_it.count > Max) {
          m_it.count = Min;
          ++m_it.loop;
        }
        break;
      }
      case RandomTint: {
        int current_idx = random_in_range(Min, Max);
        bool tint = false;
        if(m_exclude_list[current_idx])
          tint = true;

        switch(m_currentTheme)
        {
          case Light: ret = m_light_palette.at((BaseColor)current_idx).lighter(100 + (tint ? m_it.loop * 20 : m_it.loop * 10)).name(); break;
          case Dark: ret = m_dark_palette.at((BaseColor)current_idx).darker(100 + (tint ? m_it.loop * 20 : m_it.loop * 10)).name(); break;
        }

        ++m_it.count;
        m_exclude_list[current_idx] = true;
        if(m_it.count > Max) {
          m_it.count = Min;
          ++m_it.loop;

          for(auto& state : m_exclude_list)
            state = false;
        }
        break;
      }
    }

    return ret;
  }

  QString ColorProvider::exactColor(ColorProvider::BaseColor base_color) const
  {
    switch(m_currentTheme)
    {
      case Dark: return m_dark_palette.at(base_color).name();
      case Light: return m_light_palette.at(base_color).name();
    }

    return "#FF00FF";
  }

  void ColorProvider::reset() noexcept { m_it = {0, 0}; }

  ColorProvider::ThemeVariant ColorProvider::theme() const { return m_currentTheme; }
  void ColorProvider::setTheme(ColorProvider::ThemeVariant var)
  {
    if(m_currentTheme == var)
      return;
    m_currentTheme = var;
    emit themeChanged();

    this->reset();
  }

  ColorProvider::DistributionBehavior ColorProvider::behavior() const { return m_currentBehavior; }
  void ColorProvider::setBehavior(ColorProvider::DistributionBehavior var)
  {
    if(m_currentBehavior == var)
      return;
    m_currentBehavior = var;
    emit behaviorChanged();

    this->reset();
  }

  void ColorProvider::setPalette(const map<BaseColor, QColor>& new_palette, ColorProvider::ThemeVariant palette_type)
  {
    switch(palette_type)
    {
      case Light: m_light_palette = new_palette;
      case Dark: m_dark_palette = new_palette;
    }

    this->reset();
  }
} // Scenegraph::Utils