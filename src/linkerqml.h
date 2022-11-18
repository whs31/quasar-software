#ifndef LINKERQML_H
#define LINKERQML_H

//#include <mainwindow.h>
#include <QObject>
#include <QQuickItem>

class LinkerQML : public QObject
{
public:
    LinkerQML(QQuickItem* map);

    void clearImageArray();
    void hideImage(QVariant i);
    void showImage(QVariant i);
    void addImage(double latitude, double longitude, float dx, float dy, float x0, float y0, float angle, QString filename, float height);
protected:
    QQuickItem* map;
};

#endif // LINKERQML_H
