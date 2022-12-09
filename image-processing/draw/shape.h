#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QVector>
#include <QPoint>

class Shape : QObject
{
    Q_OBJECT
public:
    explicit Shape();
    int getLowerBound();
    int getUpperBound();
    int getLeftBound();
    int getRightBound();

protected:
    QVector<QPoint> points;
    int lowerBound = 0;
    int upperBound = 0;
    int leftBound = 0;
    int rightBound = 0;
    void checkBounds();
signals:

};

#endif // SHAPE_H
