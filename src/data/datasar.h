#ifndef DATASAR_H
#define DATASAR_H

#include <QObject>

class DataSAR : public QObject
{
    Q_OBJECT

    // общие переменные с РЛС
    Q_PROPERTY(qreal freeDiskSpace                  READ getFreeDiskSpace       WRITE setFreeDiskSpace       NOTIFY freeDiskSpaceChanged)
    Q_PROPERTY(qreal totalDiskSpace                 READ getTotalDiskSpace      WRITE setTotalDiskSpace      NOTIFY totalDiskSpaceChanged)

public:
    static DataSAR* get(QObject* parent = nullptr);

    qreal getFreeDiskSpace() const;                                     void setFreeDiskSpace(qreal value);
    qreal getTotalDiskSpace() const;                                    void setTotalDiskSpace(qreal value);
 
signals:
    void freeDiskSpaceChanged();
    void totalDiskSpaceChanged();

private:
    static DataSAR* _instance;
    explicit DataSAR(QObject *parent = nullptr);

    qreal freeDiskSpace = 0;
    qreal totalDiskSpace = 0;

};

#endif // DATASAR_H
