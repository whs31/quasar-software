#ifndef TMARKER_H
#define TMARKER_H

#include <QObject>

class TMarker : public QObject
{
    Q_OBJECT
public:
    explicit TMarker(QObject *parent = nullptr);

signals:

};

#endif // TMARKER_H
