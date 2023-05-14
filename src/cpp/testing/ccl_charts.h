#pragma once

#include <ccl/ccl_global.h>
#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtQuick/QQuickItem>
#include <QtQuick/QSGSimpleMaterial>

namespace ccl
{
    namespace charts
    {
        struct State
        {
            QColor color;
            int compare(const State* other) const;
        };

        struct Vertex
        {
            Vertex(float x, float y);
            float x, y;
        };

        struct VertexT
        {
            VertexT(float x, float y, float u, float v);
            float x, y, u, v;
        };

        class GLGradientShader : public QSGSimpleMaterialShader<State>
        {
            QSG_DECLARE_SIMPLE_COMPARABLE_SHADER(GLGradientShader, State)

            public:
                const char* vertexShader() const override;
                const char* fragmentShader() const override;
                QList<QByteArray> attributes() const override;
                void updateState(const State* state, const State*) override;
                void resolveUniforms() override;

            private:
                int id_color;
        };

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

            protected:
                QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

            private:
                float m_interval = 1'000; // ms
                float m_horizontalAxisMaxValue = 30'000; // ms
                float m_verticalAxisMaxValue = 1'000;
                QString m_histogramColor = "purple";
        };
    } // namespace charts;
} // namespace charts;
