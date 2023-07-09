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
  class FGSMapObject : public AbstractMapObject
  {
    public:
      // ctors

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
