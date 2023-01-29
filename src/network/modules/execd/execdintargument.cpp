#include "execdintargument.h"

ExecdIntArgument::ExecdIntArgument(QObject *parent, QString key, int defaultValue, QString description)
    : QObject{parent}, key(key), defaultvalue(defaultValue), description(description)
{
    //logging
    qDebug() << "Key: " << key << ", defaults: " << defaultValue << ", description: " << description;
    m_value = defaultValue;
}
