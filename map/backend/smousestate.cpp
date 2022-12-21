/* 
 * TODO:
 * DEPRECATED
 * rework in progress
*/

#include "smousestate.h"

short int SMouseState::mouseState = MouseState::Blank;
SMouseState::SMouseState(QObject *parent) : QObject{parent}
{}
