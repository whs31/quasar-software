#include "flightprediction.h"

FlightPrediction::FlightPrediction(QObject *parent) : QObject{parent} {}

qreal FlightPrediction::getGeometricalAngle() { return m_angles.geometrical; }
void FlightPrediction::setGeometricalAngle(qreal value)
{
    if (value == m_angles.geometrical)
        return;
    m_angles.geometrical = value;
    emit geometricalAngleChanged();
}

qreal FlightPrediction::getMercatorAngle() { return m_angles.mercator; }
void FlightPrediction::setMercatorAngle(qreal value)
{
    if (value == m_angles.mercator)
        return;
    m_angles.mercator = value;
    emit mercatorAngleChanged();
}

qreal FlightPrediction::getX0() { return m_velocityVector.start.x(); }
void FlightPrediction::setX0(qreal value)
{
    if (value == m_velocityVector.start.x() || value == m_diagramPredict.baseStart.x())
        return;
    m_velocityVector.start.setX(value);
    m_diagramPredict.baseStart.setX(value);
    emit x0Changed();
}

qreal FlightPrediction::getY0() { return m_velocityVector.start.y(); }
void FlightPrediction::setY0(qreal value)
{
    if (value == m_velocityVector.start.y() || value == m_diagramPredict.baseStart.y())
        return;
    m_velocityVector.start.setY(value);
    m_diagramPredict.baseStart.setY(value);
    emit y0Changed();
}

qreal FlightPrediction::getX1() { return m_diagramPredict.baseEnd.x(); }
void FlightPrediction::setX1(qreal value)
{
    if (value == m_diagramPredict.baseEnd.x())
        return;
    m_diagramPredict.baseEnd.setX(value);
    emit x1Changed();
}

qreal FlightPrediction::getY1() { return m_diagramPredict.baseEnd.y(); }
void FlightPrediction::setY1(qreal value)
{
    if (value == m_diagramPredict.baseEnd.y())
        return;
    m_diagramPredict.baseEnd.setY(value);
    emit y1Changed();
}

qreal FlightPrediction::getX10() { return m_velocityVector.end.x(); }
void FlightPrediction::setX10(qreal value)
{
    if (value == m_velocityVector.end.x())
        return;
    m_velocityVector.end.setX(value);
    emit x10Changed();
}

qreal FlightPrediction::getY10() { return m_velocityVector.end.y(); }
void FlightPrediction::setY10(qreal value)
{
    if (value == m_velocityVector.end.y())
        return;
    m_velocityVector.end.setY(value);
    emit y10Changed();
}

qreal FlightPrediction::getX2() { return m_diagramPredict.sideStart.x(); }
void FlightPrediction::setX2(qreal value)
{
    if (value == m_diagramPredict.sideStart.x())
        return;
    m_diagramPredict.sideStart.setX(value);
    emit x2Changed();
}

qreal FlightPrediction::getY2() { return m_diagramPredict.sideStart.y(); }
void FlightPrediction::setY2(qreal value)
{
    if (value == m_diagramPredict.sideStart.y())
        return;
    m_diagramPredict.sideStart.setY(value);
    emit y2Changed();
}

qreal FlightPrediction::getX3() { return m_diagramPredict.sideEnd.x(); }
void FlightPrediction::setX3(qreal value)
{
    if (value == m_diagramPredict.sideEnd.x())
        return;
    m_diagramPredict.sideEnd.setX(value);
    emit x3Changed();
}

qreal FlightPrediction::getY3() { return m_diagramPredict.sideEnd.y(); }
void FlightPrediction::setY3(qreal value)
{
    if (value == m_diagramPredict.sideEnd.y())
        return;
    m_diagramPredict.sideEnd.setY(value);
    emit y3Changed();
}