#include "dataformparameters.h"

DataFormParameters *DataFormParameters::_instance = nullptr;
DataFormParameters *DataFormParameters::get(QObject *parent) { if (_instance != NULL) return _instance;
    _instance = new DataFormParameters(parent); return _instance; }
DataFormParameters::DataFormParameters(QObject *parent) : QObject{parent} {}

QString DataFormParameters::getFormMode() { return mode; }
void DataFormParameters::setFormMode(QString string) { if (string == mode) return;
    mode = string; emit formModeChanged(); }

quint32 DataFormParameters::getFormLowerBound() { return lowerBound; }
void DataFormParameters::setFormLowerBound(quint32 value) { if (value == lowerBound) return;
    lowerBound = value; emit formLowerBoundChanged(); }

quint32 DataFormParameters::getFormUpperBound() { return upperBound; }
void DataFormParameters::setFormUpperBound(quint32 value) { if (value == upperBound) return;
    upperBound = value; emit formUpperBoundChanged(); }

float DataFormParameters::getFormTime() { return time; }
void DataFormParameters::setFormTime(float value) { if (value == time) return;
    time = value; emit formTimeChanged(); }

float DataFormParameters::getFormStep() { return step; }
void DataFormParameters::setFormStep(float value) { if (value == step) return;
    step = value; emit formStepChanged(); }

int DataFormParameters::getFormOverrideGPSData() { return overrideGPS; }
void DataFormParameters::setFormOverrideGPSData(int state) { if (state == overrideGPS) return;
    overrideGPS = state; emit formOverrideGPSDataChanged(); }

float DataFormParameters::getFormGPSHeight() { return gpsHeight; }
void DataFormParameters::setFormGPSHeight(float value) { if (value == gpsHeight) return;
    gpsHeight = value; emit formGPSHeightChanged(); }

float DataFormParameters::getFormGPSVelocity() { return gpsVelocity; }
void DataFormParameters::setFormGPSVelocity(float value) { if (value == gpsVelocity) return;
    gpsVelocity = value; emit formGPSVelocityChanged(); }

bool DataFormParameters::getFormingContinuous() { return formingContinuous; }
void DataFormParameters::setFormingContinuous(bool state) { if (state == formingContinuous) return;
    formingContinuous = state; emit formingContinuousChanged(); }

int DataFormParameters::getFormingQueueMode() { return queueMode; }
void DataFormParameters::setFormingQueueMode(int state) { if (state == queueMode) return;
    queueMode = state; emit formingQueueModeChanged(); }
