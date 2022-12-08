#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>

class LinkerQML : public QObject
{
public:
    LinkerQML(QQuickItem* map);

    void clearImageArray(void);
    void hideImage(QVariant i);
    void showImage(QVariant i);
    void addImage(double latitude, double longitude, float dx, float dy,
                  float x0, float y0, float angle, QString filename,
                  float height, QString base64encoding);
    void fixedUpdate();
    void panGPS(void);
    void clearRoute(void);
    void panImage(int filecounter);

protected:
    QQuickItem* map;
};

#endif // LINKERQML_H
