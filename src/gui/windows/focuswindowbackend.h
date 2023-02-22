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
    Q_PROPERTY(qreal time           READ time         WRITE timeSet              NOTIFY timeChanged)
    Q_PROPERTY(qreal sideLength     READ sideLength   WRITE sideLengthSet        NOTIFY sideLengthChanged)

public:
    static FocusWindowBackend* get(QObject* parent = nullptr);
    Q_INVOKABLE void show(void) override;

    QString base64() const;             void base64Set(const QString &newBase64);
    QString filename() const;           void filenameSet(const QString &newFilename);
    qreal x() const;                    void xSet(qreal newX);
    qreal y() const;                    void ySet(qreal newY);
    qreal time() const;                 void timeSet(qreal newTime);
    qreal sideLength() const;           void sideLengthSet(qreal newSideLength);

signals:
    void base64Changed();
    void filenameChanged();
    void xChanged();
    void yChanged();
    void timeChanged();
    void sideLengthChanged();

private:
    explicit FocusWindowBackend(QObject *parent = nullptr);
    static FocusWindowBackend* pointer;

    QString m_base64;
    QString m_filename;
    qreal m_x;
    qreal m_y;
    qreal m_time;
    qreal m_sideLength;
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
