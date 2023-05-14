#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtQuick/QQuickPaintedItem>

namespace ccl
{
    class RealtimeHistogram : public QQuickPaintedItem
    {
        Q_OBJECT
        PROPERTY_DEF(float, interval, setInterval, m_interval)
        PROPERTY_DEF(float, horizontalAxisMaxValue, setHorizontalAxisMaxValue, m_horizontalAxisMaxValue)
        PROPERTY_DEF(float, verticalAxisMaxValue, setVerticalAxisMaxValue, m_verticalAxisMaxValue)
        PROPERTY_DEF(QString, histogramColor, setHistogramColor, m_histogramColor)
        PROPERTY_DEF(QString, backgroundColor, setBackgroundColor, m_backgroundColor)
        PROPERTY_DEF(QString, axisColor, setAxisColor, m_axisColor)
        PROPERTY_DEF(QString, axisFont, setAxisFont, m_axisFont)

        public:
            RealtimeHistogram(QQuickItem* parent = nullptr);

            __exposed void append(float value);

            signals:
                __property_signal intervalChanged();
                __property_signal horizontalAxisMaxValueChanged();
                __property_signal verticalAxisMaxValueChanged();
                __property_signal histogramColorChanged();
                __property_signal backgroundColorChanged();
                __property_signal axisColorChanged();
                __property_signal axisFontChanged();

        private:
            float m_interval = 1'000; // ms
            float m_horizontalAxisMaxValue = 30'000; // ms
            float m_verticalAxisMaxValue = 1'000;
            QString m_histogramColor = "purple";
            QString m_backgroundColor = "black";
            QString m_axisColor = "white";
            QString m_axisFont = "Helvetica";
    };
}
