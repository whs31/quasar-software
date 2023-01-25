#ifndef SCALEGRIDBACKEND_H
#define SCALEGRIDBACKEND_H

#include <QObject>

class ScaleGridBackend : public QObject
{
    Q_OBJECT
public:
    explicit ScaleGridBackend(QObject *parent = nullptr);

signals:

};

#endif // SCALEGRIDBACKEND_H
