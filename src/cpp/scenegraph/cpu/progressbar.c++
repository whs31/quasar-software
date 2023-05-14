#include "progressbar.h"
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <cmath>


ProgressBar::ProgressBar(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}

void ProgressBar::paint(QPainter* painter)
{
    QPen pen(Qt::PenStyle::NoPen);
    QBrush brush(Qt::BrushStyle::SolidPattern);
    QBrush background_brush(Qt::BrushStyle::SolidPattern);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    if(value() < 35)
        brush.setColor(QColor(errorColor()));
    else if(value() > 65)
        brush.setColor(QColor(successColor()));
    else
        brush.setColor(QColor(warnColor()));

    background_brush.setColor(QColor(backgroundColor()));
    painter->setBrush(background_brush);

    painter->drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);

    painter->setBrush(brush);
    painter->drawRoundedRect(0, 0, this->width() * (float)value() / 100, this->height(), 4, 4);
}
