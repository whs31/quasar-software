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

void FocusWindowBackend::filenameSet(QString newFilename)
{
    if (m_filename == newFilename)
        return;
    m_filename = newFilename;
    m_filename.chop(4);
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

qreal FocusWindowBackend::lx() const
{
    return m_lx;
}

void FocusWindowBackend::lxSet(qreal newLX)
{
    if (qFuzzyCompare(m_lx, newLX))
        return;
    m_lx = newLX;
    emit lxChanged();
}

qreal FocusWindowBackend::ly() const
{
    return m_ly;
}

void FocusWindowBackend::lySet(qreal newLY)
{
    if (qFuzzyCompare(m_ly, newLY))
        return;
    m_ly = newLY;
    emit lyChanged();
}

qreal FocusWindowBackend::step() const
{
    return m_step;
}

void FocusWindowBackend::stepSet(qreal newStep)
{
    if (qFuzzyCompare(m_step, newStep))
        return;
    m_step = newStep;
    emit stepChanged();
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

qreal FocusWindowBackend::offset() const
{
    return m_offset;
}

void FocusWindowBackend::offsetSet(qreal newOffset)
{
    if (qFuzzyCompare(m_offset, newOffset))
        return;
    m_offset = newOffset;
    emit offsetChanged();
}

void FocusWindowBackend::reform(void)
{
    setReturnCode(2);
    setShown(false);
    RuntimeData::get()->windowLockSet(false);
}
