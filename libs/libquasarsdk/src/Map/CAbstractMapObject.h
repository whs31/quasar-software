/**
 *  \file CAbstractMapObject.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IMapObject.h"

namespace QuasarSDK::Map
  {
    /**
     * \brief Абстрактный класс, реализующий функции интерфейса IMapObject, за исключением масштаба.
     */
    class AbstractMapObject : public IMapObject
    {
      public:
        [[nodiscard]] QGeoCoordinate coordinate() const final;
        void setCoordinate(const QGeoCoordinate& coord) final;
        virtual void setCoordinate(double latitude, double longitude);

        [[nodiscard]] QPointF origin() const final;
        void setOrigin(const QPointF& point) final;
        virtual void setOrigin(float x, float y);

        [[nodiscard]] float opacity() const final;
        void setOpacity(float val) final;

        [[nodiscard]] bool isVisible() const final;
        void setVisible(bool state) final;

      protected:
        AbstractMapObject();
        explicit AbstractMapObject(const QGeoCoordinate& coord, const QPointF& origin_point = {0, 0},
                                   float opacity_value = 1, bool visibility = true);

      protected:
        float m_zoomLevel;

      private:
        QGeoCoordinate m_coordinate;
        QPointF m_origin;
        float m_opacity;
        bool m_visible;
    };
  } // QuasarSDK::Map
