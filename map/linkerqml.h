#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>
#include <QVector>
#include "models/tmarker.h"
#include "models/timage.h"

class LinkerQML : public QObject
{
    Q_OBJECT
public:
    static LinkerQML* initialize(QQuickItem* map = nullptr);

    static void fixedUpdate(void);
    static void panGPS(void);
    static void clearRoute(void);
    static void panImage(void);

    static void addModel(TMarker& marker);
    static void addModel(TImage& image);

    //emulator
    static void startFlightEmulator(void);

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
