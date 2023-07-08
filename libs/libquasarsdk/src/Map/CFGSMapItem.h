/**
 *  \file CFGSMapItem.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapItem.h"

namespace QuasarSDK::Map
{
  class FGSMapItem : public AbstractMapItem
  {
    public:
      [[nodiscard]] float zoomLevel() const final;
      void setZoomLevel(float val) final;

      [[nodiscard]] virtual float ratio() const;
      virtual void setRatio(float r);

    protected:
      static float calculate_mercator_zoom_level(double lat, float meters_per_px) noexcept;

    protected:
      float m_ratio;
  };
} // QuasarSDK::Map
