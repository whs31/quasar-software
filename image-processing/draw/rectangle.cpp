#include "rectangle.h"

Rectangle::Rectangle(QPoint a, QPoint b, QPoint c, QPoint d) 
{
    points.clear();
    points.append(a);
    points.append(b);
    points.append(c);
    points.append(d);
    checkBounds();
}
