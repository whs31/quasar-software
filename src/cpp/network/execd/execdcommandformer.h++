#pragma once

#include <definitions.h++>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

struct execdargument_t
{
    constexpr __global uint8_t FLOATING_POINT_PRECISION = 1;

    enum Type
    {
        Float,
        Integer,
        String
    };

    QString name = "invalid name";
    QString key = "--invalid";
    Type type = Integer;
    QVariant default_value = -1;
    QString description = "No description";

    QString string()
    {
        if(type == Float)
            return QString::number(value.toFloat(), 'f', FLOATING_POINT_PRECISION);
        if(type == Integer)
            return QString::number(value.toInt());
        else
            return value.toString();
    }

    void set(QVariant val)
    {
        value = val;
    }

    private:
        QVariant value = default_value;
};

class ExecdCommandFormer : public QObject
{
    Q_OBJECT

    public:
        explicit ExecdCommandFormer(QObject* parent = nullptr);

        signals:

    private:

};

