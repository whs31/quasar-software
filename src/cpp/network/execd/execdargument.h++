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
        Float = 0,
        Integer,
        String
    };

    execdargument_t(QString key, Type type, QVariant default_value, QString description = "No description")
        : key(key)
        , type(type)
        , default_value(default_value)
        , description(description)
    {}

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

//Q_DECLARE_METATYPE(execdargument_t);
