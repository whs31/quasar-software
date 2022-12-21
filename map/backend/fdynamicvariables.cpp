/* 
 * TODO:
 * DEPRECATED
 * rework in progress
*/

#include "fdynamicvariables.h"

FDynamicVariables::FDynamicVariables(QObject *parent)
    : QObject{parent}
{
    _followPlane = false;
    _enableTooltip = true;
    _enableRoute = true;
    _enablePredict = true;
    _enablePredictDiagram = true;
}

bool FDynamicVariables::followPlane()    { return _followPlane; }
void FDynamicVariables::setFollowPlane(bool value)  { if(value == _followPlane) return; _followPlane = value; emit followPlaneChanged(_followPlane); }

bool FDynamicVariables::enableTooltip()   { return _enableTooltip; }
void FDynamicVariables::setEnableTooltip(bool value) { if(value == _enableTooltip) return; _enableTooltip = value; emit enableTooltipChanged(); }

bool FDynamicVariables::enableRoute()   { return _enableRoute; }
void FDynamicVariables::setEnableRoute(bool value) { if(value == _enableRoute) return; _enableRoute = value; emit enableRouteChanged(); }

bool FDynamicVariables::enablePredict()       { return _enablePredict; }
void FDynamicVariables::setEnablePredict(bool value)     { if(value == _enablePredict) return; _enablePredict = value; emit enablePredictChanged(); }

bool FDynamicVariables::enablePredictDiagram()        { return _enablePredictDiagram; }
void FDynamicVariables::setEnablePredictDiagram(bool value)      { if(value == _enablePredictDiagram) return; _enablePredictDiagram = value; emit enablePredictDiagramChanged(); }
