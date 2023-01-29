#ifndef EXECDREALARGUMENT_H
#define EXECDREALARGUMENT_H

#include <QObject>
#include <QDebug>

class ExecdRealArgument : public QObject
{
    Q_OBJECT
public:
    explicit ExecdRealArgument(QObject *parent = nullptr, QString key = "invalid", float defaultValue = -1, QString description = "No description yet");
    QString key = "-invalid";
    QString description = "Invalid description";
    float defaultvalue = -1;

    bool isChanged(void) {
        if(defaultvalue == m_value)
            return false;
        return true;
    }

    void setValue(float value) { m_value = value; }


signals:

private:
    float m_value = -1;
};

#endif // EXECDARGUMENT_H
