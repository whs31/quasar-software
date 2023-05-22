#pragma once

#include "LPVL/Global"
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace LPVL
{
    class MatrixPlot : public QQuickItem
    {
        Q_OBJECT

        public:
            MatrixPlot(QQuickItem* parent = nullptr);

            void set(const vector<vector<float>>& array2d);
            void set(const vector<vector<int>> array2d);
            void set(const vector<vector<uint8_t>> array2d);

            QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

        private:
            vector<vector<float>> data;
    };
} // LPVL

