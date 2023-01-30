#ifndef MARKERWINDOWBACKEND_H
#define MARKERWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"
#include "map/models/marker.h"
#include "abstract/windowbackend.h"

class MarkerWindowBackend : public WindowBackend
{
    Q_OBJECT

public:
    static MarkerWindowBackend* get(QObject* parent = nullptr);

signals:

private:
    explicit MarkerWindowBackend(QObject *parent = nullptr);
    static MarkerWindowBackend* pointer;

    QString m_name = "Marker Name";
    qreal m_lat = -1;
    qreal m_lon = -1;
    bool m_record = true;
    bool m_screenAnchor = true;
    qint8 m_colorCode = -1;
    qint8 m_iconCode = -1;
};

#endif // MARKERWINDOWBACKEND_H
