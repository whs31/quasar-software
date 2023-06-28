#pragma once

#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace SDK::Quick
{
  class MatrixPlot : public QQuickItem
  {
    Q_OBJECT
      Q_PROPERTY(float tintRed READ tintRed WRITE setTintRed NOTIFY tintRedChanged)
      Q_PROPERTY(float tintGreen READ tintGreen WRITE setTintGreen NOTIFY tintGreenChanged)
      Q_PROPERTY(float tintBlue READ tintBlue WRITE setTintBlue NOTIFY tintBlueChanged)
      Q_PROPERTY(float brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
      Q_PROPERTY(bool grayscale READ grayscale WRITE setGrayscale NOTIFY grayscaleChanged)

    public:
      explicit MatrixPlot(QQuickItem* parent = nullptr);

      Q_INVOKABLE void set(const vector<float>& array2d, int rows, int columns);
      Q_INVOKABLE void set(const vector<int>& array2d, int rows, int columns);
      Q_INVOKABLE void set(const vector<uint8_t>& array2d, int rows, int columns);
      Q_INVOKABLE void clean();

      [[nodiscard]] float tintRed() const; void setTintRed(float);
      [[nodiscard]] float tintGreen() const; void setTintGreen(float);
      [[nodiscard]] float tintBlue() const; void setTintBlue(float);
      [[nodiscard]] float brightness() const; void setBrightness(float);
      [[nodiscard]] bool grayscale() const; void setGrayscale(bool);

    signals:
      void tintRedChanged();
      void tintGreenChanged();
      void tintBlueChanged();
      void brightnessChanged();
      void grayscaleChanged();

    protected:
      QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

    private:
      vector<vector<float>> data;
      float m_tintRed;
      float m_tintGreen;
      float m_tintBlue;
      float m_brightness;
      float current_max;
      bool m_grayscale;
  };
} // SDK::Quick