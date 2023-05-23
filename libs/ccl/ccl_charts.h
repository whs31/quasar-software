#pragma once

#include "ccl_global.h"
#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

class QTimer;

namespace ccl
{
    namespace charts
    {
        struct CCL_CORE_EXPORT State
        {
            QColor color;
            int compare(const State* other) const;
        };

        struct CCL_CORE_EXPORT Vertex
        {
            Vertex(float x, float y);
            float x, y;
        };

        struct CCL_CORE_EXPORT VertexT
        {
            VertexT(float x, float y, float u, float v);
            float x, y, u, v;
        };

        class CCL_CORE_EXPORT RealtimeHistogram : public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(float interval READ interval WRITE setInterval NOTIFY intervalChanged)
            Q_PROPERTY(float horizontalAxisMaxValue READ horizontalAxisMaxValue WRITE setHorizontalAxisMaxValue NOTIFY horizontalAxisMaxValueChanged)
            Q_PROPERTY(float verticalAxisMaxValue READ verticalAxisMaxValue WRITE setVerticalAxisMaxValue NOTIFY verticalAxisMaxValueChanged)
            Q_PROPERTY(QString histogramColor READ histogramColor WRITE setHistogramColor NOTIFY histogramColorChanged)

            public:
                RealtimeHistogram(QQuickItem* parent = nullptr);

                Q_INVOKABLE void append(float value);

                float interval() const;
                void setInterval(float);

                float horizontalAxisMaxValue() const;
                void setHorizontalAxisMaxValue(float);

                float verticalAxisMaxValue() const;
                void setVerticalAxisMaxValue(float);

                QString histogramColor() const;
                void setHistogramColor(const QString&);

                signals:
                    void intervalChanged();
                    void horizontalAxisMaxValueChanged();
                    void verticalAxisMaxValueChanged();
                    void histogramColorChanged();

            protected:
                QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

            private:
                QTimer* timer;
                vector<float> storage;
                int storage_size;
                float stored;

                float m_interval = 1'000; // ms
                float m_horizontalAxisMaxValue = 30'000; // ms
                float m_verticalAxisMaxValue = 1'000;
                QString m_histogramColor = "purple";
        };
    } // namespace charts;
} // namespace ccl;
