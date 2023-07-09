/**
 *  \file CScreenMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CAbstractMapObject.h"
#include <stdexcept>

namespace QuasarSDK::Map
{
  /// \brief Базовый класс для объектов карты, привязанных по размеру к экрану.
  class ScreenMapObject : public AbstractMapObject
  {
    public:
      ScreenMapObject();
      explicit ScreenMapObject(const QGeoCoordinate& coord, const QPointF& origin_point = {0, 0},
                               float opacity_level = 1, bool visibility = true);

      [[nodiscard]] float zoomLevel() const final;
      void setZoomLevel(float) final;
  };

  /// \brief Всегда возвращает 0.
  float ScreenMapObject::zoomLevel() const { return 0; }

  /**
   * \brief Не используется.
   * \throws std::runtime_error
   * \note Вызов этой функции выбрасывает исключение std::runtime_error.
   */
  void ScreenMapObject::setZoomLevel(float) { throw std::runtime_error("Assignment of zoom level to ScreenMapItem is not allowed"); }

  /**
   * \brief Создает объект ScreenMapObject со значениями по умолчанию.
   * \details По умолчанию объект будет расположен в координате <tt>0, 0</tt>.
   */
  ScreenMapObject::ScreenMapObject()
    : AbstractMapObject()
  {}

  /**
   * \brief Создает объект ScreenMapObject с указанными значениями.
   * \param coord - географическая координата объекта.
   * \param origin_point - точка привязки (в пикселях от верхнего левого края). По умолчанию: <tt>[0, 0]</tt>.
   * \param opacity_level - прозрачность объекта. По умолчанию: 1.
   * \param visibility - видимость объекта. По умолчанию: <tt>true</tt>.
   */
  ScreenMapObject::ScreenMapObject(const QGeoCoordinate& coord, const QPointF& origin_point, float opacity_level, bool visibility)
      : AbstractMapObject(coord, origin_point, opacity_level, visibility)
  {}
} // QuasarSDK::Map


