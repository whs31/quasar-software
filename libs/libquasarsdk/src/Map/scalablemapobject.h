/**
 *  \file CScalableMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/basicmapobject.h"

namespace QuasarSDK::Map
{
  class ScalableMapObject : public BasicMapObject
  {
    public:
      [[nodiscard]] float zoomLevel() const final;
      virtual void setZoomLevel(float val);
  };

  inline float ScalableMapObject::zoomLevel() const { return m_zoomLevel; }
  inline void ScalableMapObject::setZoomLevel(float val) { m_zoomLevel = val; }
} // QuasarSDK::Map
