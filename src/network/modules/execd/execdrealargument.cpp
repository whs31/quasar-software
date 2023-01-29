#include "execdrealargument.h"

ExecdRealArgument::ExecdRealArgument(QObject *parent, QString key, float defaultValue, QString description)
    : QObject{parent}, key(key), defaultvalue(defaultValue), description(description)
{
    //logging
    qDebug() << "Key: " << key << ", defaults: " << defaultValue << ", description: " << description;
    m_value = defaultValue;
}
