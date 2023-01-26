#ifndef PROFILER_H
#define PROFILER_H

#include <QObject>
#include <QElapsedTimer>
#include <QVector>
#include <QMessageBox>

class Profiler : public QObject
{
    Q_OBJECT
public:
    explicit Profiler(QString profilerName = "Профайлер", bool showProfiler = true);
    void ShowProfile();
    void Start();
    void Stop(QString name = "");

private:
    void SaveProfile(QString name, float elapsed);
    QStringList operationName; 
    QVector<float> operationTime;
    QElapsedTimer* timer;
    QString header;
    bool showProfiler;


signals:

};

#endif // PROFILER_H
