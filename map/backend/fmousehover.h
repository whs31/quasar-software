/* #ifndef FMOUSEHOVER_H
#define FMOUSEHOVER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "qqml.h"

class FMouseHover : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal mousePositionX READ mousePositionX WRITE setMousePositionX NOTIFY mousePositionXChanged);
    Q_PROPERTY(qreal mousePositionY READ mousePositionY WRITE setMousePositionY NOTIFY mousePositionYChanged);
    QML_ELEMENT

public:
    static FMouseHover* initialize();
    
    qreal mousePositionX();
    qreal mousePositionY();
    //Q_INVOKABLE static void updateBoundingBox(qreal minLatitude, qreal maxLatitude, qreal minLongitude, qreal maxLongitude);
    Q_INVOKABLE static void tellScreenPosition(qreal x, qreal y, qint32 index, qint32 type); //тут же size, type, rotation и вся эта херня (потом)
    

    void setMousePositionX(qreal value);
    void setMousePositionY(qreal value);
    

signals:
    void mousePositionXChanged();
    void mousePositionYChanged();

private:
    explicit FMouseHover();
    static FMouseHover* _instance;

    static void update();

    static const qint16 markerSizeStatic[2];

    static qint16 mousePosition[2];
    //static qreal boundingBox[4];
    static QVector<qint16[6]> boundingBox; //min x, max x, min y, max y, index, type (marker = 0)
};

#endif // FMOUSEHOVER_H
 */