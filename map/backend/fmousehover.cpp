/* #include "fmousehover.h"

//размер маркера, не привязанного к zoomLevel.
const qint16 FMouseHover::markerSizeStatic[2] = {32, 32};

qint16 FMouseHover::mousePosition[2] = {0, 0};
//qreal FMouseHover::boundingBox[4] = {0, 0, 0, 0};

QVector<qint16[6]> FMouseHover::boundingBox = {};

FMouseHover* FMouseHover::_instance = nullptr;
FMouseHover::FMouseHover() { }
FMouseHover* FMouseHover::initialize()
{
    if(_instance != nullptr)
        return _instance;
    _instance = new FMouseHover();
    return _instance;
}

qreal FMouseHover::mousePositionX() { return (qreal)FMouseHover::mousePosition[0]; }
void FMouseHover::setMousePositionX(qreal value) { 
    if(value == (qreal)FMouseHover::mousePosition[0]) return; 
    FMouseHover::mousePosition[0] = (qint16)value; emit mousePositionXChanged(); update();
}

qreal FMouseHover::mousePositionY() { return (qreal)FMouseHover::mousePosition[1]; }
void FMouseHover::setMousePositionY(qreal value) { 
    if(value == (qreal)FMouseHover::mousePosition[1]) return; 
    FMouseHover::mousePosition[1] = (qint16)value; emit mousePositionYChanged(); update();
}

/* void FMouseHover::updateBoundingBox(qreal minLatitude, qreal maxLatitude, qreal minLongitude, qreal maxLongitude) {
    boundingBox[0] = minLatitude; boundingBox[1] = maxLatitude; boundingBox[2] = minLongitude; boundingBox[3] = maxLongitude;
} */
/*
void FMouseHover::tellScreenPosition(qreal x, qreal y, qint32 index, qint32 type)
{
    qint16 local[6];
    if(type == 1)
    {
        local[0] = ((qint16)x)-(markerSizeStatic[1] / 2);
        local[1] = ((qint16)x)+(markerSizeStatic[1] / 2);
        local[2] = ((qint16)y)-(markerSizeStatic[2] / 2);
        local[3] = ((qint16)y)+(markerSizeStatic[2] / 2);
        local[4] = (qint16)type;
        local[5] = (qint16)index;
    }
    qWarning()<<local;
    boundingBox.append(local);
}

void FMouseHover::update()
{
    
}
 */