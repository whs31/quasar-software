#ifndef PROFILER_H
#define PROFILER_H

#include <QObject>
#include <QElapsedTimer>
#include <QVector>
#include <QMessageBox>

#include "sconfig.h"

class Profiler : public QObject
{
    Q_OBJECT
public:
    explicit Profiler(QString profilerName = "Профайлер");
    void ShowProfile();
    void Start();
    void Stop(QString name = "");

private:
    void SaveProfile(QString name, float elapsed);
    QStringList operationName; 
    QVector<float> operationTime;
    QElapsedTimer* timer;
    QString header;


signals:

};

#endif // PROFILER_H
