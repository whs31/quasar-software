#pragma once

#include <QtGui/QColor>
#include <utility>

class IColorable
{
  public:
    IColorable();
    explicit IColorable(QColor new_color);

    [[nodiscard]] QColor color() const;
    virtual void setColor(const QColor& new_color);

  protected:
    QColor m_color;
};

inline IColorable::IColorable()
    : m_color(QColor())
{}

inline IColorable::IColorable(QColor name)
    : m_color(std::move(name))
{}

inline QColor IColorable::color() const { return m_color; }
inline void IColorable::setColor(const QColor& new_color) { m_color = new_color; }
