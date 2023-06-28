#pragma once

#include <QtQuick/QQuickItem>

namespace SDK::Quick
{
  class ChartBase : public QQuickItem
  {
    Q_OBJECT
      Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
      Q_PROPERTY(QString foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
      Q_PROPERTY(QString plottingColor READ plottingColor WRITE setPlottingColor NOTIFY plottingColorChanged)
      Q_PROPERTY(bool drawBackground READ drawBackground WRITE setDrawBackground NOTIFY drawBackgroundChanged)

    public:
      explicit ChartBase(QQuickItem* parent = nullptr);
      ~ChartBase() override = default;

      Q_INVOKABLE void forceUpdate() noexcept;

      [[nodiscard]] QString backgroundColor() const; void setBackgroundColor(const QString&);
      [[nodiscard]] QString foregroundColor() const; void setForegroundColor(const QString&);
      [[nodiscard]] QString plottingColor() const; void setPlottingColor(const QString&);
      [[nodiscard]] bool drawBackground() const; void setDrawBackground(bool);

    signals:
      void backgroundColorChanged();
      void foregroundColorChanged();
      void plottingColorChanged();
      void drawBackgroundChanged();

    private:
      QString m_backgroundColor;
      QString m_foregroundColor;
      QString m_plottingColor;
      bool m_drawBackground;
  };
} // SDK::Quick