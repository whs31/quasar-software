#ifndef MARKERWINDOWBACKEND_H
#define MARKERWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"
#include "map/models/marker.h"
#include "abstract/windowbackend.h"

class MarkerWindowBackend : public WindowBackend
{
    Q_OBJECT
    Q_PROPERTY(QString name         READ getName            WRITE setName            NOTIFY nameChanged)
    Q_PROPERTY(qreal latitude       READ getLatitude        WRITE setLatitude        NOTIFY latitudeChanged)
    Q_PROPERTY(qreal longitude      READ getLongitude       WRITE setLongitude       NOTIFY longitudeChanged)
    Q_PROPERTY(bool record          READ getRecord          WRITE setRecord          NOTIFY recordChanged)
    Q_PROPERTY(bool screenAnchor    READ getScreenAnchor    WRITE setScreenAnchor    NOTIFY screenAnchorChanged)
    Q_PROPERTY(bool autocapture     READ getAutocapture     WRITE setAutocapture     NOTIFY autocaptureChanged)
    Q_PROPERTY(qint8 colorCode      READ getColorCode       WRITE setColorCode       NOTIFY colorCodeChanged)
    Q_PROPERTY(qint8 iconCode       READ getIconCode        WRITE setIconCode        NOTIFY iconCodeChanged)

public:
    static MarkerWindowBackend* get(QObject* parent = nullptr);
    int counter = 0;

    QString getName() const;
    void setName(const QString &newName);

    qreal getLatitude() const;
    void setLatitude(qreal newLatitude);

    qreal getLongitude() const;
    void setLongitude(qreal newLongitude);

    bool getRecord() const;
    void setRecord(bool newRecord);

    bool getScreenAnchor() const;
    void setScreenAnchor(bool newScreenAnchor);

    bool getAutocapture() const;
    void setAutocapture(bool newAutocapture);

    qint8 getColorCode() const;
    void setColorCode(qint8 newColorCode);

    qint8 getIconCode() const;
    void setIconCode(qint8 newIconCode);

signals:
    void nameChanged();
    void latitudeChanged();
    void longitudeChanged();
    void recordChanged();
    void screenAnchorChanged();
    void autocaptureChanged();
    void colorCodeChanged();
    void iconCodeChanged();

private:
    explicit MarkerWindowBackend(QObject *parent = nullptr);
    static MarkerWindowBackend* pointer;

    QString m_name = "Marker Name";
    qreal m_lat = -1;
    qreal m_lon = -1;
    bool m_record = true;
    bool m_screenAnchor = true;
    bool m_autocapture = false;
    qint8 m_colorCode = -1;
    qint8 m_iconCode = 1;
    qreal m_latitude;
    qreal m_longitude;
};

#endif // MARKERWINDOWBACKEND_H
