#ifndef DIALOGWINDOWBACKEND_H
#define DIALOGWINDOWBACKEND_H

#include <QObject>

class DialogWindowBackend : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit DialogWindowBackend(QObject *parent = nullptr);

signals:

};

#endif // DIALOGWINDOWBACKEND_H
