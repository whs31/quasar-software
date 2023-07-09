/**
 *  \file CMapImage.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "CFGSMapObject.h"
#include "ISARImage.h"

namespace QuasarSDK::Map
{
  /**
   * \brief Абстрактный класс, описывающий радиолокационное изображение в качестве объекта карты.
   */
  class MapImage : public FGSMapObject,
                   public ISARImage
  {
    public:
      /**
       * \brief Создает объект MapImage со значениями по умолчанию.
       */
      MapImage();

      /**
       * \brief Создает объект MapImage с указанными значениями.
       * \param coord - координаты привязки изображение.
       * \param offset - смещение изображение в метрах по осям X и Y (м).
       * \param rect - размер прямоугольника, ограничивающего изображение (м).
       * \param angle - азимутальный угол поворота изображения в градусах от севера.
       * \param dx_ratio - количество метров на один пиксель.
       * \param origin_point - точка привязки (в пикселях).
       */
      MapImage(const QGeoCoordinate& coord, const QPointF& offset, const QSizeF& rect,
               float angle, float dx_ratio = 1, const QPointF& origin_point = {0, 0});

      [[nodiscard]] float azimuth() const override;
      void setAzimuth(float deg) override;

      [[nodiscard]] QPointF offset() const override;
      void setOffset(const QPointF& point) override;

      [[nodiscard]] QSizeF rectSize() const override;
      void setRectSize(const QSizeF& size) override;

    private:
      float m_azimuth;
      QPointF m_offset;
      QSizeF m_rectSize;
  };
} // QuasarSDK::Map
