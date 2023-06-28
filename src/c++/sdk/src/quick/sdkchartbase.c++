#include "sdkchartbase.h"

namespace SDK::Quick
{
  ChartBase::ChartBase(QQuickItem* parent)
      : QQuickItem(parent)
      , m_backgroundColor("black")
      , m_foregroundColor("white")
      , m_plottingColor("purple")
      , m_drawBackground(true)
  {
    this->setFlags(ItemHasContents);
  }

  void ChartBase::forceUpdate() noexcept { this->update(); }

  QString ChartBase::backgroundColor() const { return m_backgroundColor; }
  void ChartBase::setBackgroundColor(const QString& o) {
    if (m_backgroundColor == o)
      return;
    m_backgroundColor = o;
    emit backgroundColorChanged();

    this->update();
  }

  QString ChartBase::foregroundColor() const { return m_foregroundColor; }
  void ChartBase::setForegroundColor(const QString& o) {
    if (m_foregroundColor == o)
      return;
    m_foregroundColor = o;
    emit foregroundColorChanged();

    this->update();
  }

  QString ChartBase::plottingColor() const { return m_plottingColor; }
  void ChartBase::setPlottingColor(const QString& o) {
    if (m_plottingColor == o)
      return;
    m_plottingColor = o;
    emit plottingColorChanged();

    this->update();
  }

  bool ChartBase::drawBackground() const { return m_drawBackground; }
  void ChartBase::setDrawBackground(bool o) {
    if (m_drawBackground == o)
      return;
    m_drawBackground = o;
    emit drawBackgroundChanged();

    this->update();
  }
} // SDK::Quick