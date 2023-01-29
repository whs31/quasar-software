#include "execdstrargument.h"

ExecdStringArgument::ExecdStringArgument(QObject *parent, QString key, QString defaultValue, QString description)
    : QObject{parent}, key(key), defaultvalue(defaultValue), description(description)
{
    //logging
    qDebug() << "Key: " << key << ", defaults: " << defaultValue << ", description: " << description;
    m_value = defaultValue;
}
