#pragma once

#include "LPVL/Global"
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace LPVL
{
    class LPVL_EXPORT MatrixPlot : public QQuickItem
    {
        Q_OBJECT

        public:
            MatrixPlot(QQuickItem* parent = nullptr);
            virtual ~MatrixPlot() = default;

            Q_INVOKABLE void set(const vector<float>& array2d, int rows, int columns);
            Q_INVOKABLE void set(const vector<int> array2d, int rows, int columns);
            Q_INVOKABLE void set(const vector<uint8_t> array2d, int rows, int columns);

            QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

        private:
            vector<vector<float>> data;
    };
} // LPVL

