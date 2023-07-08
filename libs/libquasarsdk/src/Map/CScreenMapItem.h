/**
 *  \file CScreenMapItem.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapItem.h"
#include <stdexcept>

namespace QuasarSDK::Map
{
  /// \brief Базовый класс для объектов карты, привязанных по размеру к экрану.
  class ScreenMapItem : public AbstractMapItem
  {
    public:
      [[nodiscard]] float zoomLevel() const final;
      void setZoomLevel(float) final;
  };

  /// \brief Всегда возвращает 0.
  float ScreenMapItem::zoomLevel() const { return 0; }

  /**
   * \brief Не используется.
   * \throws std::runtime_error
   * \note Вызов этой функции выбрасывает исключение std::runtime_error.
   */
  void ScreenMapItem::setZoomLevel(float) { throw std::runtime_error("Assignment of zoom level to ScreenMapItem is not allowed"); }
} // QuasarSDK::Map
