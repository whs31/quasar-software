#ifndef FOCUSWINDOWBACKEND_H
#define FOCUSWINDOWBACKEND_H

#include <QObject>
#include "abstract/windowbackend.h"

class FocusWindowBackend : public WindowBackend
{
    Q_OBJECT
    Q_PROPERTY(QString base64       READ base64       WRITE base64Set            NOTIFY base64Changed)
    Q_PROPERTY(QString filename     READ filename     WRITE filenameSet          NOTIFY filenameChanged)
    Q_PROPERTY(qreal x              READ x            WRITE xSet                 NOTIFY xChanged)
    Q_PROPERTY(qreal y              READ y            WRITE ySet                 NOTIFY yChanged)
    Q_PROPERTY(qreal lx             READ lx           WRITE lxSet                NOTIFY lxChanged)
    Q_PROPERTY(qreal ly             READ ly           WRITE lySet                NOTIFY lyChanged)
    Q_PROPERTY(qreal step           READ step         WRITE stepSet              NOTIFY stepChanged)
    Q_PROPERTY(qreal offset         READ offset       WRITE offsetSet            NOTIFY offsetChanged)
    Q_PROPERTY(qreal time           READ time         WRITE timeSet              NOTIFY timeChanged)
    Q_PROPERTY(qreal sideLength     READ sideLength   WRITE sideLengthSet        NOTIFY sideLengthChanged)

public:
    static FocusWindowBackend* get(QObject* parent = nullptr);
    Q_INVOKABLE void show(void) override;

    QString base64() const;             void base64Set(const QString &newBase64);
    QString filename() const;           void filenameSet(QString newFilename);
    qreal x() const;                    void xSet(qreal newX);
    qreal y() const;                    void ySet(qreal newY);
    qreal lx() const;                   void lxSet(qreal newLX);
    qreal ly() const;                   void lySet(qreal newLY);
    qreal step() const;                 void stepSet(qreal newStep);
    qreal time() const;                 void timeSet(qreal newTime);
    qreal sideLength() const;           void sideLengthSet(qreal newSideLength);

    qreal offset() const;
    void offsetSet(qreal newOffset);

signals:
    void base64Changed();
    void filenameChanged();
    void xChanged();
    void yChanged();
    void lxChanged();
    void lyChanged();
    void stepChanged();
    void timeChanged();
    void sideLengthChanged();

    void offsetChanged();

private:
    explicit FocusWindowBackend(QObject *parent = nullptr);
    static FocusWindowBackend* pointer;

    QString m_base64;
    QString m_filename;
    qreal m_x;
    qreal m_y;
    qreal m_lx;
    qreal m_ly;
    qreal m_step;
    qreal m_time;
    qreal m_sideLength;
    qreal m_offset;
};

inline void FocusWindowBackend::show()
{
    xSet(0);
    ySet(0);
    timeSet(1);
    sideLengthSet(25);
    setReturnCode(0);
    setShown(true);
}

#endif // FOCUSWINDOWBACKEND_H
