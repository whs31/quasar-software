#ifndef EXECDINTARGUMENT_H
#define EXECDINTARGUMENT_H

#include <QObject>
#include <QDebug>

class ExecdIntArgument : public QObject
{
    Q_OBJECT
public:
    explicit ExecdIntArgument(QObject *parent = nullptr, QString key = "invalid", int defaultValue = -1, QString description = "No description yet");
    QString key = "-invalid";
    QString description = "Invalid description";
    int defaultvalue = -1;

    bool isChanged(void) {
        if(defaultvalue == m_value)
            return false;
        return true;
    }

    void setValue(int value) { m_value = value; }

signals:

private:
    int m_value = -1;


};

#endif // EXECDARGUMENT_H
