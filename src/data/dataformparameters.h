#ifndef DATAFORMPARAMETERS_H
#define DATAFORMPARAMETERS_H

#include <QObject>
#include "network/modules/execd/argumentlist.h"

class DataFormParameters : public QObject
{
    Q_OBJECT

    // параметры формирования
    Q_PROPERTY(QString formMode                     READ getFormMode            WRITE setFormMode            NOTIFY formModeChanged)
    Q_PROPERTY(quint32 formLowerBound               READ getFormLowerBound      WRITE setFormLowerBound      NOTIFY formLowerBoundChanged)
    Q_PROPERTY(quint32 formUpperBound               READ getFormUpperBound      WRITE setFormUpperBound      NOTIFY formUpperBoundChanged)
    Q_PROPERTY(float formTime                       READ getFormTime            WRITE setFormTime            NOTIFY formTimeChanged)
    Q_PROPERTY(float formStep                       READ getFormStep            WRITE setFormStep            NOTIFY formStepChanged)
    Q_PROPERTY(int formOverrideGPSData              READ getFormOverrideGPSData WRITE setFormOverrideGPSData NOTIFY formOverrideGPSDataChanged)
    Q_PROPERTY(float formGPSHeight                  READ getFormGPSHeight       WRITE setFormGPSHeight       NOTIFY formGPSHeightChanged)
    Q_PROPERTY(float formGPSVelocity                READ getFormGPSVelocity     WRITE setFormGPSVelocity     NOTIFY formGPSVelocityChanged)
    Q_PROPERTY(bool formingContinuous               READ getFormingContinuous   WRITE setFormingContinuous   NOTIFY formingContinuousChanged)
    Q_PROPERTY(int formingQueueMode                 READ getFormingQueueMode    WRITE setFormingQueueMode    NOTIFY formingQueueModeChanged)
    Q_PROPERTY(float timeshift                      READ getTimeshift           WRITE setTimeshift           NOTIFY timeshiftChanged)
    Q_PROPERTY(float reformVelocity                 READ getReformVelocity      WRITE setReformVelocity      NOTIFY reformVelocityChanged)

    // параметры фокусировки
    Q_PROPERTY(QString filename                     READ filename               WRITE filenameSet            NOTIFY filenameChanged)
    Q_PROPERTY(qreal focusX                         READ focusX                 WRITE focusXSet              NOTIFY focusXChanged)
    Q_PROPERTY(qreal focusY                         READ focusY                 WRITE focusYSet              NOTIFY focusYChanged)
    Q_PROPERTY(qreal focusL                         READ focusL                 WRITE focusLSet              NOTIFY focusLChanged)
    Q_PROPERTY(qreal focusTime                      READ focusTime              WRITE focusTimeSet           NOTIFY focusTimeChanged)

public:
    static DataFormParameters* get(QObject* parent = nullptr);

    QString getFormMode();                                              void setFormMode(QString string);
    quint32 getFormLowerBound();                                        void setFormLowerBound(quint32 value);
    quint32 getFormUpperBound();                                        void setFormUpperBound(quint32 value);
    float getFormTime();                                                void setFormTime(float value);
    float getFormStep();                                                void setFormStep(float value);
    int getFormOverrideGPSData();                                       void setFormOverrideGPSData(int state);
    float getFormGPSHeight();                                           void setFormGPSHeight(float value);
    float getFormGPSVelocity();                                         void setFormGPSVelocity(float value);
    bool getFormingContinuous();                                        void setFormingContinuous(bool state);
    int getFormingQueueMode();                                          void setFormingQueueMode(int state);

    QString filename() const;
    void filenameSet(const QString &newFilename);

    qreal focusX() const;
    void focusXSet(qreal newFocusX);

    qreal focusY() const;
    void focusYSet(qreal newFocusY);

    qreal focusL() const;
    void focusLSet(qreal newFocusL);

    qreal focusTime() const;
    void focusTimeSet(qreal newFocusTime);

    float getTimeshift() const;
    void setTimeshift(float newTimeshift);

    float getReformVelocity() const;
    void setReformVelocity(float newReformVelocity);

signals:
    void formModeChanged();
    void formLowerBoundChanged();
    void formUpperBoundChanged();
    void formTimeChanged();
    void formStepChanged();
    void formOverrideGPSDataChanged();
    void formGPSHeightChanged();
    void formGPSVelocityChanged();
    void formingContinuousChanged();
    void formingQueueModeChanged();


    void filenameChanged();

    void focusXChanged();

    void focusYChanged();

    void focusLChanged();

    void focusTimeChanged();

    void timeshiftChanged();

    void reformVelocityChanged();

private:
    static DataFormParameters* _instance;
    explicit DataFormParameters(QObject *parent = nullptr);

    QString mode = "m1";
    quint32 lowerBound = 100;
    quint32 upperBound = 2000;
    float time = 1;
    float step = 1;
    int overrideGPS = 0;
    float gpsHeight = 150;
    float gpsVelocity = 100;
    bool formingContinuous = false;
    int queueMode = 0; //0 = Single     1 = Continuous
    QString m_filename;
    qreal m_focusX;
    qreal m_focusY;
    qreal m_focusL;
    qreal m_focusTime;
    float m_timeshift;
    float m_reformVelocity;
};

#endif // DATAFORMPARAMETERS_H
