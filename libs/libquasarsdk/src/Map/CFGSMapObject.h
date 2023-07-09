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
  class FGSMapObject : public AbstractMapItem
  {
    public:
      // ctors

      [[nodiscard]] float zoomLevel() const final;
      void setZoomLevel(float val) final;

      [[nodiscard]] virtual float ratio() const;
      virtual void setRatio(float r);

    protected:
      static float calculate_mercator_zoom_level(double lat, float meters_per_px) noexcept;

    private:
      float m_ratio;
  };
} // QuasarSDK::Map
