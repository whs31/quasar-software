#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>
#include <QVector>

#include "models/marker.h"
#include "models/image.h"

class LinkerQML : public QObject
{
    Q_OBJECT
public:
    static LinkerQML* get(QQuickItem* map = nullptr);

    static void fixedUpdate(void);
    static void callDestructor(void);
    static void panGPS(void);
    static void clearRoute(void);
    static void panImage(void);

    static void addModel(Marker& marker);
    static void addModel(Image& image);

    //emulator
    static void startFlightEmulator(void);

    static void removeMarker(int index);

signals:
    void signalReconnect();
    void signalDisconnect();

public slots:
    void reconnect();
    void disconnect(); 

protected:
    static QQuickItem* map;

private:
    LinkerQML(QObject* parent = nullptr);
    static LinkerQML* _instance;

};

#endif // LINKERQML_H
