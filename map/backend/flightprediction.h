#ifndef FLIGHTPREDICTION_H
#define FLIGHTPREDICTION_H

#include <QObject>
#include <qqml.h>
#include <QPoint>
#include "smath.h"
#include <cmath>
#include "sconfig.h"
#include "runtimedata.h"
#include "global/markermanager.h"

class FlightPrediction : public QObject //смысл класса прост: кумл дает на вход 2 точки - текущие и предыдущие координаты, получает все углы и точки для предиктов
{
    Q_OBJECT

    //основные геометрические углы для фронтэнда
    Q_PROPERTY(qreal geometricalAngle   READ getGeometricalAngle    WRITE setGeometricalAngle   NOTIFY geometricalAngleChanged);
    Q_PROPERTY(qreal mercatorAngle      READ getMercatorAngle       WRITE setMercatorAngle      NOTIFY mercatorAngleChanged);

    //точки диаграммы направленности и вектора скорости
    Q_PROPERTY(qreal x0                 READ getX0                  WRITE setX0                 NOTIFY x0Changed);
    Q_PROPERTY(qreal y0                 READ getY0                  WRITE setY0                 NOTIFY y0Changed);
    Q_PROPERTY(qreal x1                 READ getX1                  WRITE setX1                 NOTIFY x1Changed);
    Q_PROPERTY(qreal y1                 READ getY1                  WRITE setY1                 NOTIFY y1Changed);
    Q_PROPERTY(qreal x10                READ getX10                 WRITE setX10                NOTIFY x10Changed);
    Q_PROPERTY(qreal y10                READ getY10                 WRITE setY10                NOTIFY y10Changed);
    Q_PROPERTY(qreal x2                 READ getX2                  WRITE setX2                 NOTIFY x2Changed);
    Q_PROPERTY(qreal y2                 READ getY2                  WRITE setY2                 NOTIFY y2Changed);
    Q_PROPERTY(qreal x3                 READ getX3                  WRITE setX3                 NOTIFY x3Changed);
    Q_PROPERTY(qreal y3                 READ getY3                  WRITE setY3                 NOTIFY y3Changed);

    QML_ELEMENT
public:
    FlightPrediction(QObject* parent = nullptr);

    const qreal AUTOCAPTURE_TOLERANCE_IN_METERS = 25;

    // ==> GET ==>
    qreal getGeometricalAngle();
    qreal getMercatorAngle();
    qreal getX0();
    qreal getY0();
    qreal getX1();
    qreal getY1();
    qreal getX10();
    qreal getY10();
    qreal getX2();
    qreal getY2();
    qreal getX3();
    qreal getY3();

    // <== SET <==
    void setGeometricalAngle(qreal value);
    void setMercatorAngle(qreal value);
    void setX0(qreal value);
    void setY0(qreal value);
    void setX1(qreal value);
    void setY1(qreal value);
    void setX10(qreal value);
    void setY10(qreal value);
    void setX2(qreal value);
    void setY2(qreal value);
    void setX3(qreal value);
    void setY3(qreal value);

    void calculateIntersections(QGeoCoordinate p1, QGeoCoordinate p2);

signals:
    // =!= NOTIFY =!=
    void geometricalAngleChanged();
    void mercatorAngleChanged();
    void x0Changed();
    void y0Changed();
    void x1Changed();
    void y1Changed();
    void x10Changed();
    void y10Changed();
    void x2Changed();
    void y2Changed();
    void x3Changed();
    void y3Changed();


private:
    struct Angles
    {
        qreal geometrical = 0;
        qreal mercator = 0;
    }; Angles m_angles;
    

    struct VelocityVector 
    {
        QPointF start;
        QPointF end;
    }; VelocityVector m_velocityVector;
    
    struct DiagramPredict
    {
        QPointF baseStart;
        QPointF baseEnd;
        QPointF sideStart;
        QPointF sideEnd;
    }; DiagramPredict m_diagramPredict;

    bool m_waitForAnotherAxisTrigger = false;
    
    void updatePoints();
};

#endif // FLIGHTPREDICTION_H
