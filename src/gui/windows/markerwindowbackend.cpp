#include "markerwindowbackend.h"

MarkerWindowBackend* MarkerWindowBackend::pointer = nullptr;
MarkerWindowBackend* MarkerWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new MarkerWindowBackend(parent);
    return pointer;
}
MarkerWindowBackend::MarkerWindowBackend(QObject *parent)
    : WindowBackend{parent}
{
    show();
}

QString MarkerWindowBackend::getName() const { return m_name; }
void MarkerWindowBackend::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

qreal MarkerWindowBackend::getLatitude() const { return m_latitude; }
void MarkerWindowBackend::setLatitude(qreal newLatitude)
{
    if (qFuzzyCompare(m_latitude, newLatitude))
        return;
    m_latitude = newLatitude;
    emit latitudeChanged();
}

qreal MarkerWindowBackend::getLongitude() const { return m_longitude; }
void MarkerWindowBackend::setLongitude(qreal newLongitude)
{
    if (qFuzzyCompare(m_longitude, newLongitude))
        return;
    m_longitude = newLongitude;
    emit longitudeChanged();
}

bool MarkerWindowBackend::getRecord() const { return m_record; }
void MarkerWindowBackend::setRecord(bool newRecord)
{
    if (m_record == newRecord)
        return;
    m_record = newRecord;
    emit recordChanged();
}

bool MarkerWindowBackend::getScreenAnchor() const { return m_screenAnchor; }
void MarkerWindowBackend::setScreenAnchor(bool newScreenAnchor)
{
    if (m_screenAnchor == newScreenAnchor)
        return;
    m_screenAnchor = newScreenAnchor;
    emit screenAnchorChanged();
}

qint8 MarkerWindowBackend::getColorCode() const { return m_colorCode; }
void MarkerWindowBackend::setColorCode(qint8 newColorCode)
{
    if (m_colorCode == newColorCode)
        return;
    m_colorCode = newColorCode;
    emit colorCodeChanged();
}

qint8 MarkerWindowBackend::getIconCode() const { return m_iconCode; }
void MarkerWindowBackend::setIconCode(qint8 newIconCode)
{
    if (m_iconCode == newIconCode)
        return;
    m_iconCode = newIconCode;
    emit iconCodeChanged();
}
