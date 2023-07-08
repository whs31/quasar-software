/**
 *  \file CAbstractMapItem.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IMapItem.h"

namespace QuasarSDK::Map
  {
    /**
     * \brief Абстрактный класс, реализующий функции интерфейса IMapItem, за исключением масштаба.
     */
    class AbstractMapItem : public IMapItem
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
        QGeoCoordinate m_coordinate;
        QPointF m_origin;
        float m_zoomLevel;
        float m_opacity;
        bool m_visible;
    };
  } // QuasarSDK::Map
