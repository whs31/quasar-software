#include "runtimedata.h"

RuntimeData *RuntimeData::_instance = nullptr;
short int RuntimeData::mouseState = MouseState::Blank;
RuntimeData *RuntimeData::initialize(QObject *parent) { if (_instance != NULL) return _instance;
_instance = new RuntimeData(parent); return _instance; }
RuntimeData::RuntimeData(QObject *parent) : QObject{parent} {}

qreal RuntimeData::getLatitude() { return telemetry.latitude; }
void RuntimeData::setLatitude(qreal value) { if (value == telemetry.latitude) return;
telemetry.latitude = value; emit latitudeChanged(); }

qreal RuntimeData::getLongitude() { return telemetry.longitude; }
void RuntimeData::setLongitude(qreal value) { if (value == telemetry.longitude) return;
telemetry.longitude = value; emit longitudeChanged(); }

qreal RuntimeData::getElevation() { return telemetry.elevation; }
void RuntimeData::setElevation(qreal value) { if (value == telemetry.elevation) return;
telemetry.elevation = value; emit elevationChanged(); }

qreal RuntimeData::getSpeed() { return telemetry.speed; }
void RuntimeData::setSpeed(qreal value) { if (value == telemetry.speed) return;
telemetry.speed = value; emit speedChanged(); }

qreal RuntimeData::getSeaLevel() { return telemetry.seaLevel; }
void RuntimeData::setSeaLevel(qreal value) { if (value == telemetry.seaLevel) return;
telemetry.seaLevel = value; emit seaLevelChanged(); }

qint16 RuntimeData::getSatellites() { return telemetry.satellites; }
void RuntimeData::setSatellites(short value) { if (value == telemetry.satellites) return; 
telemetry.satellites = value; emit satellitesChanged(); }

qreal RuntimeData::getAzimuthalDirection() { return m_azimuthalDirection; }
void RuntimeData::setAzimuthalDirection(qreal value) { m_azimuthalDirection = value; }

qreal RuntimeData::getFlatDirection() { return m_flatDirection; }
void RuntimeData::setFlatDirection(qreal value) { m_flatDirection = value; } 

qreal RuntimeData::getPitch() { return aircraftAxes.pitch; }
void RuntimeData::setPitch(qreal value) { if (value == aircraftAxes.pitch) return;
aircraftAxes.pitch = value; emit pitchChanged(); }

qreal RuntimeData::getRoll() { return aircraftAxes.roll; }
void RuntimeData::setRoll(qreal value) { if (value == aircraftAxes.roll) return;
aircraftAxes.roll = value; emit rollChanged(); }

qreal RuntimeData::getYaw() { return aircraftAxes.yaw; }
void RuntimeData::setYaw(qreal value) { if (value == aircraftAxes.yaw) return;
aircraftAxes.yaw = value; emit yawChanged(); }

qreal RuntimeData::getThrottle() { return aircraftAxes.throttle; }
void RuntimeData::setThrottle(qreal value) { if (value == aircraftAxes.throttle) return;
aircraftAxes.throttle = value; emit throttleChanged(); }

bool RuntimeData::getFollowPlane() { return mapSettings.followPlane; }
void RuntimeData::setFollowPlane(bool state) { if (state == mapSettings.followPlane) return; 
mapSettings.followPlane = state; }

bool RuntimeData::getDrawTooltip() { return mapSettings.drawTooltip; }
void RuntimeData::setDrawTooltip(bool state) { if (state == mapSettings.drawTooltip) return;
mapSettings.drawTooltip = state; } //TODO: чзх где сигнал

bool RuntimeData::getDrawRoute() { return mapSettings.drawRoute; }
void RuntimeData::setDrawRoute(bool state) { if (state == mapSettings.drawRoute) return;
mapSettings.drawRoute = state; emit drawRouteChanged(); }

bool RuntimeData::getDrawPredict() { return mapSettings.drawPredict; }
void RuntimeData::setDrawPredict(bool state) { if (state == mapSettings.drawPredict) return;
mapSettings.drawPredict = state; emit drawPredictChanged(); }

bool RuntimeData::getDrawDiagram() { return mapSettings.drawDiagram; }
void RuntimeData::setDrawDiagram(bool state) { if (state == mapSettings.drawDiagram) return;
mapSettings.drawDiagram = state; emit drawDiagramChanged(); }

bool RuntimeData::getGlobal_useOSMMaps() { return SConfig::get()->getOnlineMaps(); }
qreal RuntimeData::getGlobal_velocityVectorLength() { return SConfig::get()->getVelocityVectorLength(); }

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

QString RuntimeData::getFormMode() { return formParameters.mode; }
void RuntimeData::setFormMode(QString string) { if (string == formParameters.mode) return;
formParameters.mode = string; emit formModeChanged(); }

quint32 RuntimeData::getFormLowerBound() { return formParameters.lowerBound; }
void RuntimeData::setFormLowerBound(quint32 value) { if (value == formParameters.lowerBound) return;
formParameters.lowerBound = value; emit formLowerBoundChanged(); }

quint32 RuntimeData::getFormUpperBound() { return formParameters.upperBound; }
void RuntimeData::setFormUpperBound(quint32 value) { if (value == formParameters.upperBound) return;
formParameters.upperBound = value; emit formUpperBoundChanged(); }

float RuntimeData::getFormTime() { return formParameters.time; }
void RuntimeData::setFormTime(float value) { if (value == formParameters.time) return;
formParameters.time = value; emit formTimeChanged(); }

float RuntimeData::getFormStep() { return formParameters.step; }
void RuntimeData::setFormStep(float value) { if (value == formParameters.step) return;
formParameters.step = value; emit formStepChanged(); }

int RuntimeData::getFormOverrideGPSData() { return formParameters.overrideGPS; }
void RuntimeData::setFormOverrideGPSData(int state) { if (state == formParameters.overrideGPS) return;
formParameters.overrideGPS = state; emit formOverrideGPSDataChanged(); }

float RuntimeData::getFormGPSHeight() { return formParameters.gpsHeight; }
void RuntimeData::setFormGPSHeight(float value) { if (value == formParameters.gpsHeight) return;
formParameters.gpsHeight = value; emit formGPSHeightChanged(); }

float RuntimeData::getFormGPSVelocity() { return formParameters.gpsVelocity; }
void RuntimeData::setFormGPSVelocity(float value) { if (value == formParameters.gpsVelocity) return;
formParameters.gpsVelocity = value; emit formGPSVelocityChanged(); }

bool RuntimeData::getFormingContinuous() { return formParameters.formingContinuous; }
void RuntimeData::setFormingContinuous(bool state) { if (state == formParameters.formingContinuous) return;
formParameters.formingContinuous = state; emit formingContinuousChanged(); }

int RuntimeData::getFormingQueueMode() { return formParameters.queueMode; }
void RuntimeData::setFormingQueueMode(int state) { if (state == formParameters.queueMode) return;
formParameters.queueMode = state; emit formingQueueModeChanged(); }

qreal RuntimeData::getAutocaptureDistance() const { return autocaptureVariables.distance; }
void RuntimeData::setAutocaptureDistance(qreal newAutocaptureDistance) { if (autocaptureVariables.distance == newAutocaptureDistance) return;
autocaptureVariables.distance = newAutocaptureDistance; emit autocaptureDistanceChanged(); }

bool RuntimeData::getAutocaptureEnabled() const { return autocaptureVariables.enabled; }
void RuntimeData::setAutocaptureEnabled(bool state) { if (autocaptureVariables.enabled == state) return;
autocaptureVariables.enabled = state; emit autocaptureEnabledChanged(); }

qreal RuntimeData::getFreeDiskSpace() const { return sarCommonVariables.freeDiskSpace / (1000 * 1000); }
void RuntimeData::setFreeDiskSpace(qreal value) { if (sarCommonVariables.freeDiskSpace == value) return;
sarCommonVariables.freeDiskSpace = value; emit freeDiskSpaceChanged(); }

qreal RuntimeData::getTotalDiskSpace() const { return sarCommonVariables.totalDiskSpace / (1000 * 1000); }
void RuntimeData::setTotalDiskSpace(qreal value) { if (sarCommonVariables.totalDiskSpace == value) return;
sarCommonVariables.totalDiskSpace = value; emit totalDiskSpaceChanged(); }

void RuntimeData::autocapture(void) { emit autocaptureSignal(); }
void RuntimeData::clearSARDisk(void) { emit clearSARDiskSignal(); }
