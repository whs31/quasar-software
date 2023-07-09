/**
 *  \file CFGSMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapObject.h"

namespace QuasarSDK::Map
{
  /**
   * \brief Базовый класс для объектов карты, которые имеют четкую привязку в метрах по размеру.
   * \details Разрешение в пикселях на метр задается свойство ratio и setRatio.
   */
  class FGSMapObject : public AbstractMapObject
  {
    public:
      /// \brief Создает объект с параметрами по умолчанию.
      FGSMapObject();

      /**
       * \brief Создает объект FGSMapObject с указанными параметрами.
       * \param coord - координата объекта.
       * \param dpx_ratio - разрешение в метрах на один пиксель для объекта. По умолчанию: 1.
       * \param origin_point - точка привязки в пикселях. По умолчанию: <tt>[0, 0]</tt>.
       * \param opacity_value - значение прозрачности. По умолчанию: 1.
       * \param visibility - видимость объекта. По умолчанию: <tt>true</tt>.
       */
      explicit FGSMapObject(const QGeoCoordinate& coord, float dpx_ratio = 1, const QPointF& origin_point = {0, 0},
                   float opacity_value = 0, bool visibility = true);

      [[nodiscard]] float zoomLevel() const final;

      [[nodiscard]] virtual float ratio() const; /// \brief Возвращает текущее количество метров на один пиксель.
      virtual void setRatio(float r);            /// \brief Задает текущее количество метров на один пиксель.

    protected:
      /**
       * \brief Внутренняя функция для расчета zoomLevel QtLocationMapQuickItem с указанным разрешением в м/пкс.
       * \param lat - широта, на которой находится объект.
       * \param meters_per_px - количество метро на один пиксель.
       * \return Значение zoomLevel.
       */
      static float calculate_mercator_zoom_level(double lat, float meters_per_px) noexcept;

    private:
      float m_ratio;
  };
} // QuasarSDK::Map
