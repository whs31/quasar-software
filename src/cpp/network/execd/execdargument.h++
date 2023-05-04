#pragma once

#include <definitions.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

struct execdargument_t
{
    enum Type
    {
        Float = 0,
        Integer,
        String
    };

    constexpr __global uint8_t FLOATING_POINT_PRECISION = 1;

    execdargument_t(QString key, Type type, QVariant default_value, QString description = "No description");
    QString string();
    void set(QVariant val);

    QString key = "--invalid";
    Type type = Integer;
    QVariant default_value = -1;
    QString description = "No description";

    private:
        QVariant value = default_value;
};

inline execdargument_t::execdargument_t(QString key, Type type, QVariant default_value, QString description)
    : key(key)
    , type(type)
    , default_value(default_value)
    , description(description)
{}

inline QString execdargument_t::string()
{
    if(type == Float)
        return QString::number(value.toFloat(), 'f', FLOATING_POINT_PRECISION);
    if(type == Integer)
        return QString::number(value.toInt());
    else
        return value.toString();
}

inline void execdargument_t::set(QVariant val)
{
    value = val;
}
