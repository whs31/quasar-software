#ifndef LINKERQML_H
#define LINKERQML_H

//#include <mainwindow.h>
#include <QObject>
#include <QQuickItem>

class LinkerQML : public QObject
{
public:
    LinkerQML(QQuickItem* map);

    void clearImageArray(void);
    void hideImage(QVariant i);
    void showImage(QVariant i);
    void addImage(double latitude, double longitude, float dx, float dy, float x0, float y0, float angle, QString filename, float height);
    void getTelemetry(float f1, float f2, float f3, float f4);
    void changeEnableTooltip(QVariant arg1);
    void changeDrawRoute(QVariant arg1);
    void changeFollowPlane(QVariant arg1);
    void panGPS(void);
    void clearRoute(void);
    void panImage(int filecounter);

protected:
    QQuickItem* map;
};

#endif // LINKERQML_H
