#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "draw/shape.h"
#include <QDebug>

class Rectangle : public Shape
{
public:
    explicit Rectangle(QPoint a = QPoint(0, 0), QPoint b = QPoint(0, 0), QPoint c = QPoint(0, 0), QPoint d = QPoint(0, 0));
};

#endif // RECTANGLE_H
