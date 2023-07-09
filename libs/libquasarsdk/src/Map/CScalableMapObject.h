/**
 *  \file CScalableMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapObject.h"

namespace QuasarSDK::Map
{
  class ScalableMapObject : public AbstractMapObject
  {
    public:
      [[nodiscard]] float zoomLevel() const final;
      virtual void setZoomLevel(float val);
  };

  float ScalableMapObject::zoomLevel() const { return m_zoomLevel; }
  void ScalableMapObject::setZoomLevel(float val) { m_zoomLevel = val; }
} // QuasarSDK::Map
