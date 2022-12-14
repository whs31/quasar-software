#ifndef DISKTOOLS_H
#define DISKTOOLS_H

#include <QObject>

class DiskTools : public QObject
{
    Q_OBJECT
public:
    static DiskTools* initialize(QObject* parent); 

signals:

private:
    static DiskTools* _instance;
    explicit DiskTools(QObject *parent = nullptr);

};

#endif // DISKTOOLS_H
