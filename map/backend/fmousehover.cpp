#include "fmousehover.h"

qreal FMouseHover::_mousePositionX = 0;
qreal FMouseHover::_mousePositionY = 0;
FMouseHover* FMouseHover::_instance = nullptr;
FMouseHover::FMouseHover() { }
FMouseHover* FMouseHover::initialize()
{
    if(_instance != nullptr)
        return _instance;
    _instance = new FMouseHover();
    return _instance;
}

qreal FMouseHover::mousePositionX() { return FMouseHover::_mousePositionX; }
void FMouseHover::setMousePositionX(qreal value) { if(value == FMouseHover::_mousePositionX) return; FMouseHover::_mousePositionX = value; emit mousePositionXChanged(); }

qreal FMouseHover::mousePositionY() { return FMouseHover::_mousePositionY; }
void FMouseHover::setMousePositionY(qreal value) { if(value == FMouseHover::_mousePositionY) return; FMouseHover::_mousePositionY = value; emit mousePositionYChanged(); }
