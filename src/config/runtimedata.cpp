#include "runtimedata.h"

RuntimeData *RuntimeData::_instance = nullptr;
RuntimeData *RuntimeData::get(QObject *parent) { if (_instance != NULL) return _instance;
_instance = new RuntimeData(parent); return _instance; }
RuntimeData::RuntimeData(QObject *parent) : QObject{parent} {}
void RuntimeData::closeAllWindows(void)
{
    windowLockSet(false);
    infoWindowSet(false);
    settingsWindowSet(false);
    markerWindowSet(false);
    passwordWindowSet(false);
}


quint8 RuntimeData::getMouseState() const { return m_mouseState; }
void RuntimeData::setMouseState(quint8 state) { if (m_mouseState == state) return;
m_mouseState = state; emit mouseStateChanged(); }

qreal RuntimeData::getAzimuthalDirection() { return m_azimuthalDirection; }
void RuntimeData::setAzimuthalDirection(qreal value) { m_azimuthalDirection = value; }

qreal RuntimeData::getFlatDirection() { return m_flatDirection; }
void RuntimeData::setFlatDirection(qreal value) { m_flatDirection = value; } 

qreal RuntimeData::getCurrentZoomLevel() { return m_currentZoomLevel; }
void RuntimeData::setCurrentZoomLevel(qreal value) { if (value == m_currentZoomLevel) return;
m_currentZoomLevel = value; emit currentZoomLevelChanged(); }

bool RuntimeData::getFollowPlane() { return mapSettings.followPlane; }
void RuntimeData::setFollowPlane(bool state) { if (state == mapSettings.followPlane) return; 
mapSettings.followPlane = state; emit followPlaneChanged(); }

bool RuntimeData::getDrawGrid() { return mapSettings.drawGrid; }
void RuntimeData::setDrawGrid(bool state) { if (state == mapSettings.drawGrid) return;
mapSettings.drawGrid = state; emit drawGridChanged(); } 

bool RuntimeData::getDrawTooltip() { return mapSettings.drawTooltip; }
void RuntimeData::setDrawTooltip(bool state) { if (state == mapSettings.drawTooltip) return;
mapSettings.drawTooltip = state; emit drawTooltipChanged(); } 

bool RuntimeData::getDrawRoute() { return mapSettings.drawRoute; }
void RuntimeData::setDrawRoute(bool state) { if (state == mapSettings.drawRoute) return;
mapSettings.drawRoute = state; emit drawRouteChanged(); }

bool RuntimeData::getDrawPredict() { return mapSettings.drawPredict; }
void RuntimeData::setDrawPredict(bool state) { if (state == mapSettings.drawPredict) return;
mapSettings.drawPredict = state; emit drawPredictChanged(); }

bool RuntimeData::getDrawDiagram() { return mapSettings.drawDiagram; }
void RuntimeData::setDrawDiagram(bool state) { if (state == mapSettings.drawDiagram) return;
mapSettings.drawDiagram = state; emit drawDiagramChanged(); }

bool RuntimeData::getEmulatorEnabled() { return m_emulatorMode; }
void RuntimeData::setEmulatorEnabled(bool state) { if (state == m_emulatorMode) return;
m_emulatorMode = state; emit emulatorEnabledChanged(); }

bool RuntimeData::getConnected() { return connectionStatus.connected; }
void RuntimeData::setConnected(bool state) { if (state == connectionStatus.connected) return;
connectionStatus.connected = state; emit connectedChanged(); }

QString RuntimeData::getSARIP() { return connectionStatus.sarIP; }
void RuntimeData::setSARIP(QString string) { if (string == connectionStatus.sarIP) return;
connectionStatus.sarIP = string; emit SARIPChanged(); }

QString RuntimeData::getPCIP() { return connectionStatus.pcIP; }
void RuntimeData::setPCIP(QString string) { if (string == connectionStatus.pcIP) return;
connectionStatus.pcIP = string; emit PCIPChanged(); }

QString RuntimeData::getTelemetryPort() { return connectionStatus.telemetryPort; }
void RuntimeData::setTelemetryPort(QString string) { if (string == connectionStatus.telemetryPort) return;
connectionStatus.telemetryPort = string; emit telemetryPortChanged(); }

QString RuntimeData::getLoaderPort() { return connectionStatus.loaderPort; }
void RuntimeData::setLoaderPort(QString string) { if (string == connectionStatus.loaderPort) return;
connectionStatus.loaderPort = string; emit loaderPortChanged(); }

QString RuntimeData::getCommandPort() { return connectionStatus.commandPort; }
void RuntimeData::setCommandPort(QString string) { if (string == connectionStatus.commandPort) return;
connectionStatus.commandPort = string; emit commandPortChanged(); }

QString RuntimeData::getListenPort() { return connectionStatus.listenPort; }
void RuntimeData::setListenPort(QString string) { if (string == connectionStatus.listenPort) return;
connectionStatus.listenPort = string; emit listenPortChanged(); }

qreal RuntimeData::getLoadingProgress() { return connectionStatus.loadingProgress; }
void RuntimeData::setLoadingProgress(qreal value) { if (value == connectionStatus.loadingProgress) return; 
connectionStatus.loadingProgress = value; emit loadingProgressChanged(); }

qreal RuntimeData::getFormProgress() { return connectionStatus.formProgress; }
void RuntimeData::setFormProgress(qreal value) { if (value == connectionStatus.formProgress) return;
connectionStatus.formProgress = value; emit formProgressChanged(); }

QString RuntimeData::getFormStatus() { return connectionStatus.formStatus; }
void RuntimeData::setFormStatus(QString string) { if (string == connectionStatus.formStatus) return;
connectionStatus.formStatus = string; emit formStatusChanged(); }

QString RuntimeData::getLoaderStatus() { return connectionStatus.loaderStatus; }
void RuntimeData::setLoaderStatus(QString string) { if (string == connectionStatus.loaderStatus) return;
connectionStatus.loaderStatus = string; emit loaderStatusChanged(); }

qreal RuntimeData::getAutocaptureDistance() const { return autocaptureVariables.distance; }
void RuntimeData::setAutocaptureDistance(qreal newAutocaptureDistance) { if (autocaptureVariables.distance == newAutocaptureDistance) return;
autocaptureVariables.distance = newAutocaptureDistance; emit autocaptureDistanceChanged(); }

bool RuntimeData::getAutocaptureEnabled() const { return autocaptureVariables.enabled; }
void RuntimeData::setAutocaptureEnabled(bool state) { if (autocaptureVariables.enabled == state) return;
autocaptureVariables.enabled = state; emit autocaptureEnabledChanged(); }

int RuntimeData::getTotalAutocapCount() const { return autocaptureVariables.totalCount; }
void RuntimeData::setTotalAutocapCount(int value) { if (autocaptureVariables.totalCount == value) return;
autocaptureVariables.totalCount = value; emit totalAutocapCountChanged(); }

int RuntimeData::getTotalImageCount() const { return mapVariables.totalImages; }
void RuntimeData::setTotalImageCount(int value) { if (mapVariables.totalImages == value) return;
mapVariables.totalImages = value; emit totalImageCountChanged(); }

void RuntimeData::autocapture(void) { emit autocaptureSignal(); }
void RuntimeData::clearSARDisk(void) { emit clearSARDiskSignal(); }
