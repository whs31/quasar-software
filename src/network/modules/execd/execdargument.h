#ifndef EXECDARGUMENT_H
#define EXECDARGUMENT_H

#include <QObject>
#include <QDebug>
#include <QVariant>

enum ArgumentType : short int
{
    Float,
    Int,
    String
};

class ExecdArgument : public QObject
{
    Q_OBJECT
public:
    explicit ExecdArgument(QObject *parent = nullptr, ArgumentType type = ArgumentType::Float,
                           QString key = "invalid", QVariant defaultValue = -1, QString description = "No description yet");
    QString key = "-invalid";
    QString description = "Invalid description";
    QVariant defaultvalue = -1;

    bool isChanged(void) {
        if(defaultvalue == m_value)
            return false;
        return true;
    }

    void setValue(QVariant value) { m_value = value; }
    QString getValue();

signals:

private:
    QVariant m_value = -1;
    ArgumentType type;
};

inline QString ExecdArgument::getValue()
{
    if(type == ArgumentType::Float)
        return QString::number(m_value.toFloat(), 'f', 1);
    if(type == ArgumentType::String)
        return m_value.toString();
    if(type == ArgumentType::Int)
        return QString::number(m_value.toInt());
    return "Invalid type";
}

#endif // EXECDARGUMENT_H
