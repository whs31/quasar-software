#pragma once

#include <utility>
#include <QtCore/QRectF>
#include <QtCore/QMetaType>
#include <QtGui/QColor>

namespace QuasarSDK
{
  class NeuralData
  {
    Q_GADGET
    Q_PROPERTY(QString tag READ tag WRITE setTag FINAL)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect FINAL)
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)

    public:
      NeuralData();
      NeuralData(QString tag, const QRectF& rect, QColor  color);
      NeuralData(QString tag, float x1, float x2, float y1, float y2, QColor color);

      [[nodiscard]] QString tag() const;    void setTag(const QString&);
      [[nodiscard]] QRectF rect() const;    void setRect(const QRectF&);
      [[nodiscard]] QColor color() const;    void setColor(const QColor&);

    private:
      QString m_tag;
      QRectF m_rect;
      QColor m_color;
  };
} // Map

Q_DECLARE_METATYPE(QuasarSDK::NeuralData)

namespace QuasarSDK
{
  inline NeuralData::NeuralData()
    : m_tag(QString())
    , m_rect(QRectF(0, 0, 0, 0))
    , m_color("white")
  {}

  inline NeuralData::NeuralData(QString tag, const QRectF& rect, QColor color)
    : m_tag(std::move(tag))
    , m_rect(rect)
    , m_color(std::move(color))
  {}

  inline NeuralData::NeuralData(QString tag, float x1, float x2, float y1, float y2, QColor color)
    : m_tag(std::move(tag))
    , m_rect(QRectF(x1, y1, x2, y2))
    , m_color(std::move(color))
  {}

  inline QString NeuralData::tag() const { return m_tag; }
  inline void NeuralData::setTag(const QString& x) { m_tag = x; }

  inline QRectF NeuralData::rect() const { return m_rect; }
  inline void NeuralData::setRect(const QRectF& x) { m_rect = x; }

  inline QColor NeuralData::color() const { return m_color; }
  inline void NeuralData::setColor(const QColor& x) { m_color = x; }
} // Map