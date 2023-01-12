#include "flightprediction.h"

FlightPrediction::FlightPrediction(QObject *parent) : QObject{parent} {}

void FlightPrediction::calculateIntersections(QGeoCoordinate p1, QGeoCoordinate p2, QGeoCoordinate p3)
{
    for(QGeoCoordinate point : RuntimeData::initialize()->autocaptureMarks)
    {
        float s1 = (p1.latitude() - point.latitude()) * (p2.longitude() - p2.longitude())-(p2.latitude() - p1.latitude()) * (p1.longitude() - point.longitude());
        float s2 = (p2.latitude() - point.latitude()) * (p3.longitude() - p2.longitude()) - (p3.latitude() - p2.latitude()) * (p2.longitude() - point.longitude());
        float s3 = (p3.latitude() - point.latitude()) * (p2.longitude() - p3.longitude()) - (p1.latitude() - p3.latitude()) * (p3.longitude() - point.longitude());
        qInfo()<<s1<<s2<<s3;
        if(s1 < 0 && s2 < 0 && s3 < 0)
        {
            qInfo()<<"found!!!! -";
            MarkerManager::removeMarkerFromCoordinates(point);
            return;
        }
        if(s1 > 0 && s2 > 0 && s3 > 0)
        {
            qInfo() << "found!!! +";
            MarkerManager::removeMarkerFromCoordinates(point);
            return;
        }
        else 
        {
            qDebug()<<"nothin'...";
            continue;
        }
    }
}

void FlightPrediction::updatePoints()
{
    const float lx = 2500;
    qreal antennaPositionCorrection = SConfig::getHashString("AntennaPosition") == "right" ? 90 : -90;

    if(m_velocityVector.start.x() != 0 && m_velocityVector.start.y() != 0)
    {
        float divergence = (SConfig::getHashFloat("DiagramThetaAzimuth") - SConfig::getHashFloat("AzimuthPredefinedCorrection")) / 2;
        setX10(getX0()  
                + SMath::metersToDegrees(SConfig::getHashFloat("VelocityVectorLength") * 1000)
                * qSin(SMath::degreesToRadians(m_angles.geometrical))
        );
        setY10(getY0() 
                + SMath::metersToDegrees(SConfig::getHashFloat("VelocityVectorLength") * 1000)
                * qCos(SMath::degreesToRadians(m_angles.geometrical))
        );

        //вычисляем точку, удаленную от борта на Lx и повернутую на угол 
        QGeoCoordinate plane(getY0(), getX0());
        QGeoCoordinate triangleBase = plane.atDistanceAndAzimuth(lx, getMercatorAngle() + antennaPositionCorrection); 
        QGeoCoordinate triangleLeft = plane.atDistanceAndAzimuth(lx, getMercatorAngle() + antennaPositionCorrection - divergence);
        QGeoCoordinate triangleRight = plane.atDistanceAndAzimuth(lx, getMercatorAngle() + antennaPositionCorrection + divergence);
        setX1(triangleBase.longitude()); setY1(triangleBase.latitude());
        setX2(triangleLeft.longitude()); setY2(triangleLeft.latitude());
        setX3(triangleRight.longitude()); setY3(triangleRight.latitude());
        if(!RuntimeData::initialize()->autocaptureMarks.isEmpty())
        {
            calculateIntersections(plane, triangleRight, triangleLeft);
        }
    }
    m_waitForAnotherAxisTrigger = false;
}

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
    if(!m_waitForAnotherAxisTrigger)
        m_waitForAnotherAxisTrigger = true;
    else
        updatePoints();
    emit x0Changed();
}

qreal FlightPrediction::getY0() { return m_velocityVector.start.y(); }
void FlightPrediction::setY0(qreal value)
{
    if (value == m_velocityVector.start.y() || value == m_diagramPredict.baseStart.y())
        return;
    m_velocityVector.start.setY(value);
    m_diagramPredict.baseStart.setY(value);
    if(!m_waitForAnotherAxisTrigger)
        m_waitForAnotherAxisTrigger = true;
    else
        updatePoints();
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