#pragma once

#include <vector>
#include "SDK/ChartBase"

using std::vector;

namespace SDK::Quick
{
  class LinePlot : public ChartBase
  {
    Q_OBJECT
      Q_PROPERTY(bool drawAxes READ drawAxes WRITE setDrawAxes NOTIFY drawAxesChanged)
      Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)

    public:
      explicit LinePlot(QQuickItem* parent = nullptr);

      Q_INVOKABLE void set(const vector<float>& vec, float max = 0, float min = 0);
      Q_INVOKABLE void clear();

      [[nodiscard]] bool drawAxes() const; void setDrawAxes(bool);
      [[nodiscard]] bool fill() const; void setFill(bool);

    signals:
      void drawAxesChanged();
      void fillChanged();

    protected:
      QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

    private:
      void calculate_bounds(bool skip = false);

    private:
      vector<float> v;
      bool m_drawAxes;
      bool m_fill;

      float x_size, y_max, y_min;
  };
} // SDK::Quick