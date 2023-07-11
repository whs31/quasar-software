/**
 * \namespace Scenegraph
 * \brief Пространство имен для библиотеки Scenegraph.
 *
 * \namespace Scenegraph::Utils
 * \brief Пространство имен для вспомогательных классов и функций, связанных с QML Scenegraph.
 */

#include "CColorProvider.h"

namespace Scenegraph::Utils
{
  ColorProvider::ColorProvider(QObject* parent)
    : QObject(parent)
  {

  }

  QString ColorProvider::next() const
  {
    return QString();
  }

  QString ColorProvider::exactColor(ColorProvider::BaseColor base_color) const
  {
    return QString();
  }

  void ColorProvider::reset() noexcept
  {

  }

  ColorProvider::ThemeVariant ColorProvider::theme() const
  {
    return ColorProvider::Dark;
  }

  void ColorProvider::setTheme(ColorProvider::ThemeVariant var)
  {

  }

  ColorProvider::DistributionBehavior ColorProvider::behavior() const
  {
    return ColorProvider::OrderedCycle;
  }

  void ColorProvider::setBehavior(ColorProvider::DistributionBehavior var)
  {

  }

  void ColorProvider::setPalette(const map<BaseColor, QColor>& new_palette, ColorProvider::ThemeVariant palette_type)
  {

  }
} // Scenegraph::Utils