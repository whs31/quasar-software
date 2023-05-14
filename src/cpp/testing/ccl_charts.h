#pragma once

#include <ccl/ccl_global.h>
#include <QtCore/QObject>
#include <QtQuick/QQuickPaintedItem>

namespace ccl
{
    class RealtimeHistogram : public QQuickItem
    {
        Q_OBJECT
        PROPERTY_DEF(float, interval, setInterval, m_interval)
        PROPERTY_DEF(float, horizontalAxisMaxValue, setHorizontalAxisMaxValue, m_horizontalAxisMaxValue)
        PROPERTY_DEF(float, verticalAxisMaxValue, setVerticalAxisMaxValue, m_verticalAxisMaxValue)
        PROPERTY_DEF(QString, histogramColor, setHistogramColor, m_histogramColor)

        public:
            RealtimeHistogram(QQuickItem* parent = nullptr);

            Q_INVOKABLE void append(float value);

            signals:
                void intervalChanged();
                void horizontalAxisMaxValueChanged();
                void verticalAxisMaxValueChanged();
                void histogramColorChanged();

        private:
            float m_interval = 1'000; // ms
            float m_horizontalAxisMaxValue = 30'000; // ms
            float m_verticalAxisMaxValue = 1'000;
            QString m_histogramColor = "purple";
    };
}
