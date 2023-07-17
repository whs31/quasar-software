/**
 *  \file IMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>

namespace QuasarSDK::Map
{
  /**
   * \ingroup sdk_map
   * \brief Интерфейс, описывающий абстрактный объект карты.
   */
  class IMapObject
  {
    public:
      [[nodiscard]] virtual QGeoCoordinate coordinate() const = 0;  ///< Возвращает координату на карте, к которой будет привязан объект.
      virtual void setCoordinate(const QGeoCoordinate& coord) = 0;  ///< Устанавливает координату на карте, к которой будет привязан объект.

      [[nodiscard]] virtual float zoomLevel() const = 0;            ///< Возвращает масштаб объекта. Интерфейс не определяет сеттер для масштаба.

      [[nodiscard]] virtual QPointF origin() const = 0;             ///< Возвращает точку привязки на объекте (в *px*).
      virtual void setOrigin(const QPointF& point) = 0;             ///< Устанавливает точку привязки на объекте (в *px*).

      [[nodiscard]] virtual float opacity() const = 0;              ///< Возвращает прозрачность объекта от 0 до 1.
      virtual void setOpacity(float val) = 0;                       ///< Устанавливает прозрачность объекта от 0 до 1.

      [[nodiscard]] virtual bool isVisible() const = 0;             ///< Возвращает состояние видимости объекта.
      virtual void setVisible(bool state) = 0;                      ///< Устанавливает состояние видимости объекта.

  };
} // QuasarSDK::Map