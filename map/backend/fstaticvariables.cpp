/* 
 * TODO:
 * DEPRECATED
 * rework in progress
*/

#include "fstaticvariables.h"

FStaticVariables::FStaticVariables(QObject *parent)
    : QObject{parent}
{}

float FStaticVariables::predictRange()    { return _predictRange; }
void FStaticVariables::setPredictRange(float value)  { if(value == _predictRange) return; _predictRange = value; emit predictRangeChanged(); }

bool FStaticVariables::useBase64()   { return _useBase64; }
void FStaticVariables::setUseBase64(bool value) { if(value == _useBase64) return; _useBase64 = value; emit useBase64Changed(); }

bool FStaticVariables::testMode()   { return _testMode; }
void FStaticVariables::setTestMode(bool value) { if(value == _testMode) return; _testMode = value; emit testModeChanged(); }
