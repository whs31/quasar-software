/**
 *  \file CScalableMapItem.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapItem.h"

namespace QuasarSDK::Map
{
  class ScalableMapItem : public AbstractMapItem
  {
    public:
      [[nodiscard]] float zoomLevel() const final;
      void setZoomLevel(float val) final;
  };

  float ScalableMapItem::zoomLevel() const { return m_zoomLevel; }
  void ScalableMapItem::setZoomLevel(float val) { m_zoomLevel = val; }
} // QuasarSDK::Map
