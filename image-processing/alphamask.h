#ifndef ALPHAMASK_H
#define ALPHAMASK_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QBuffer>

#include "sconfig.h"
#include <QtMath>

enum MaskFormat : short int
{
    Geometric,
    AlphaSwap,
    Combined
};

class AlphaMask : QObject
{
    Q_OBJECT
public:
    explicit AlphaMask();

    static QString addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, float driftAngle = 0, MaskFormat format = MaskFormat::Geometric);
    static QImage enableAlphaSupport(QImage i);
    static QString convertToBase64(QImage image);

signals:

private:


};

#endif // ALPHAMASK_H
