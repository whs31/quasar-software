#pragma once

#include "LPVL/Global"
#include <QtQuick/QQuickItem>

namespace LPVL
{
    class MatrixPlot : public QQuickItem
    {
        Q_OBJECT

        public:
            MatrixPlot(QQuickItem* parent = nullptr);
    };
} // LPVL

