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
    ~AlphaMask();

    QString addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, MaskFormat format = MaskFormat::Geometric);
    QImage enableAlphaSupport(QImage i);
    QString convertToBase64(QImage image);

signals:

private:
    const float thetaAzimuthCorrection = 0.25; //removing black borders 


};

#endif // ALPHAMASK_H
