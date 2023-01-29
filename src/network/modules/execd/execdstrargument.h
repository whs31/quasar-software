#ifndef EXECDSTRARGUMENT_H
#define EXECDSTRARGUMENT_H

#include <QObject>
#include <QDebug>

class ExecdStringArgument : public QObject
{
    Q_OBJECT
public:
    explicit ExecdStringArgument(QObject *parent = nullptr, QString key = "invalid", QString defaultValue = "-1", QString description = "No description yet");
    QString key = "-invalid";
    QString description = "Invalid description";
    QString defaultvalue = "-1";

    bool isChanged(void) {
        if(defaultvalue == m_value)
            return false;
        return true;
    }

    void setValue(QString value) { m_value = value; }
    QString getValue() { return m_value; }

signals:

private:
    QString m_value = "-1";
};

#endif // EXECDSTRARGUMENT_H
