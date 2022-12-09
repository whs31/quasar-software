#include "shape.h"

Shape::Shape()
{
    
}

void Shape::checkBounds()
{
    for (QPoint point : points)
    {
        if(point.x() > rightBound)
            rightBound = point.x();
        if(point.x() < leftBound)
            leftBound = point.x();
        if(point.y() > upperBound)
            upperBound = point.y();
        if(point.y() < lowerBound)
            lowerBound = point.y();
    }
    
}
