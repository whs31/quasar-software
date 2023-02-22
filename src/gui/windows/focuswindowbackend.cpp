#include "focuswindowbackend.h"

FocusWindowBackend* FocusWindowBackend::pointer = nullptr;
FocusWindowBackend* FocusWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new FocusWindowBackend(parent);
    return pointer;
}
FocusWindowBackend::FocusWindowBackend(QObject *parent)
    : WindowBackend{parent}
{

}

QString FocusWindowBackend::base64() const
{
    return m_base64;
}

void FocusWindowBackend::base64Set(const QString &newBase64)
{
    if (m_base64 == newBase64)
        return;
    m_base64 = newBase64;
    emit base64Changed();
}

QString FocusWindowBackend::filename() const
{
    return m_filename;
}

void FocusWindowBackend::filenameSet(const QString &newFilename)
{
    if (m_filename == newFilename)
        return;
    m_filename = newFilename;
    emit filenameChanged();
}

qreal FocusWindowBackend::x() const
{
    return m_x;
}

void FocusWindowBackend::xSet(qreal newX)
{
    if (qFuzzyCompare(m_x, newX))
        return;
    m_x = newX;
    emit xChanged();
}

qreal FocusWindowBackend::y() const
{
    return m_y;
}

void FocusWindowBackend::ySet(qreal newY)
{
    if (qFuzzyCompare(m_y, newY))
        return;
    m_y = newY;
    emit yChanged();
}

qreal FocusWindowBackend::time() const
{
    return m_time;
}

void FocusWindowBackend::timeSet(qreal newTime)
{
    if (qFuzzyCompare(m_time, newTime))
        return;
    m_time = newTime;
    emit timeChanged();
}

qreal FocusWindowBackend::sideLength() const
{
    return m_sideLength;
}

void FocusWindowBackend::sideLengthSet(qreal newSideLength)
{
    if (qFuzzyCompare(m_sideLength, newSideLength))
        return;
    m_sideLength = newSideLength;
    emit sideLengthChanged();
}
