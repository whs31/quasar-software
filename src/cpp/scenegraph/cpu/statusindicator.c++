#include "statusindicator.h"
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <cmath>


StatusIndicator::StatusIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    this->setPerformanceHint(QQuickPaintedItem::FastFBOResizing, true);
}

void StatusIndicator::paint(QPainter* painter)
{
    QColor col_error(errorColor());
    QColor col_warn(warnColor());
    QColor col_success(successColor());

    switch (state()) {
    case 0:
    {
        QBrush brush(col_error);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    case 1:
    {
        QBrush brush(col_warn);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    case 2:
    {
        QBrush brush(col_success);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    default:
        break;
    }
}
