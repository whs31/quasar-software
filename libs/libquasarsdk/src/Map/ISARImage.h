/**
 *  \file ISARImage.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#include <QtCore/QSizeF>
#include <QtCore/QPointF>

namespace QuasarSDK::Map
{
  /**
   * \brief Интерфейс, описывающий радиолокационное изображение с РЛС.
   */
  class ISARImage
  {
    public:
      [[nodiscard]] virtual float azimuth() const = 0;     ///< Возвращает значение поворота изображения в градусах отн. севера.
      virtual void setAzimuth(float deg) = 0;              ///< Задает значение поворота изображения в градусах отн. севера.

      [[nodiscard]] virtual QPointF offset() const = 0;    ///< Возвращает смещение по осям X и Y в метрах.
      virtual void setOffset(const QPointF& point) = 0;    ///< Задает смещение по осям X и Y в метрах.

      [[nodiscard]] virtual QSizeF rectSize() const = 0;   ///< Возвращает размер изображения в метрах.
      virtual void setRectSize(const QSizeF& size) = 0;    ///< Задает размер изображения в метрах.
  };
} // QuasarSDK::Map