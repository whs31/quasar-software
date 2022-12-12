#ifndef FMOUSEHOVER_H
#define FMOUSEHOVER_H

#include <QObject>
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

    void setMousePositionX(qreal value);
    void setMousePositionY(qreal value);
    

signals:
    void mousePositionXChanged();
    void mousePositionYChanged();

private:
    explicit FMouseHover();
    static FMouseHover* _instance;

    static qreal _mousePositionX;
    static qreal _mousePositionY;

};

#endif // FMOUSEHOVER_H
