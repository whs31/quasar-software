#include "dataformparameters.h"

DataFormParameters *DataFormParameters::_instance = nullptr;
DataFormParameters *DataFormParameters::get(QObject *parent) { if (_instance != NULL) return _instance;
    _instance = new DataFormParameters(parent); return _instance; }
DataFormParameters::DataFormParameters(QObject *parent) : QObject{parent} {}

QString DataFormParameters::getFormMode() { return mode; }
void DataFormParameters::setFormMode(QString string) 
{ 
    if (string == mode) return;
    mode = string; emit formModeChanged(); 
    string.remove(0, 1); 
    ArgumentList::get(this)->mode->setValue(string); 
}

quint32 DataFormParameters::getFormLowerBound() { return lowerBound; }
void DataFormParameters::setFormLowerBound(quint32 value) { if (value == lowerBound) return;
    lowerBound = value; emit formLowerBoundChanged(); ArgumentList::get()->x0->setValue(value); }

quint32 DataFormParameters::getFormUpperBound() { return upperBound; }
void DataFormParameters::setFormUpperBound(quint32 value) { if (value == upperBound) return;
    upperBound = value; emit formUpperBoundChanged(); ArgumentList::get()->lx->setValue(value); }

float DataFormParameters::getFormTime() { return time; }
void DataFormParameters::setFormTime(float value) { if (value == time) return;
    time = value; emit formTimeChanged(); ArgumentList::get()->time->setValue(value); }

float DataFormParameters::getFormStep() { return step; }
void DataFormParameters::setFormStep(float value) { if (value == step) return;
    step = value; emit formStepChanged(); ArgumentList::get()->dx->setValue(value); 
    ArgumentList::get()->dy->setValue(value); 
}

int DataFormParameters::getFormOverrideGPSData() { return overrideGPS; }
void DataFormParameters::setFormOverrideGPSData(int state) { 
    if (state == overrideGPS) return;
    overrideGPS = state; emit formOverrideGPSDataChanged(); 
    if(state == 1)
    {
        ArgumentList::get()->elevation->setValue(getFormGPSHeight()); 
        ArgumentList::get()->velocity->setValue(getFormGPSVelocity()); 
    } else if(state == 0) {
        ArgumentList::get()->elevation->setValue(-1); 
        ArgumentList::get()->velocity->setValue(-1); 
    }
} 

float DataFormParameters::getFormGPSHeight() { return gpsHeight; }
void DataFormParameters::setFormGPSHeight(float value) { if (value == gpsHeight) return;
    gpsHeight = value; emit formGPSHeightChanged(); } 

float DataFormParameters::getFormGPSVelocity() { return gpsVelocity; }
void DataFormParameters::setFormGPSVelocity(float value) { if (value == gpsVelocity) return;
    gpsVelocity = value; emit formGPSVelocityChanged(); } //?

bool DataFormParameters::getFormingContinuous() { return formingContinuous; }
void DataFormParameters::setFormingContinuous(bool state) { if (state == formingContinuous) return;
    formingContinuous = state; emit formingContinuousChanged(); }

int DataFormParameters::getFormingQueueMode() { return queueMode; }
void DataFormParameters::setFormingQueueMode(int state) { if (state == queueMode) return;
    queueMode = state; emit formingQueueModeChanged(); }

QString DataFormParameters::filename() const
{
    return m_filename;
}

void DataFormParameters::filenameSet(const QString &newFilename)
{
    if (m_filename == newFilename)
        return;
    m_filename = newFilename;
    ArgumentList::get()->filename->setValue(filename());
    emit filenameChanged();
}

qreal DataFormParameters::focusX() const
{
    return m_focusX;
}

void DataFormParameters::focusXSet(qreal newFocusX)
{
    if (qFuzzyCompare(m_focusX, newFocusX))
        return;
    m_focusX = newFocusX;
    emit focusXChanged();
    ArgumentList::get()->rect_x->setValue(focusX());
}

qreal DataFormParameters::focusY() const
{
    return m_focusY;
}

void DataFormParameters::focusYSet(qreal newFocusY)
{
    if (qFuzzyCompare(m_focusY, newFocusY))
        return;
    m_focusY = newFocusY;
    emit focusYChanged();
    ArgumentList::get()->rect_y->setValue(focusY());
}

qreal DataFormParameters::focusL() const
{
    return m_focusL;
}

void DataFormParameters::focusLSet(qreal newFocusL)
{
    if (qFuzzyCompare(m_focusL, newFocusL))
        return;
    m_focusL = newFocusL;
    emit focusLChanged();
    ArgumentList::get()->rect_edge->setValue(focusL());
}

qreal DataFormParameters::focusTime() const
{
    return m_focusTime;
}

void DataFormParameters::focusTimeSet(qreal newFocusTime)
{
    if (qFuzzyCompare(m_focusTime, newFocusTime))
        return;
    m_focusTime = newFocusTime;
    emit focusTimeChanged();
    ArgumentList::get()->focus_time->setValue(focusTime());
}

float DataFormParameters::getTimeshift() const
{
    return m_timeshift;
}

void DataFormParameters::setTimeshift(float newTimeshift)
{
    if (qFuzzyCompare(m_timeshift, newTimeshift))
        return;
    m_timeshift = newTimeshift;
    emit timeshiftChanged();
    ArgumentList::get()->timeshift->setValue(getTimeshift());
}

float DataFormParameters::getReformVelocity() const
{
    return m_reformVelocity;
}

void DataFormParameters::setReformVelocity(float newReformVelocity)
{
    if (qFuzzyCompare(m_reformVelocity, newReformVelocity))
        return;
    m_reformVelocity = newReformVelocity;
    emit reformVelocityChanged();
    ArgumentList::get()->velocity->setValue(getReformVelocity());
}
