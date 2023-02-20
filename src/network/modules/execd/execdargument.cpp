#include "execdargument.h"
#include <QDebug>

ExecdArgument::ExecdArgument(QObject *parent, ArgumentType type, QString key, QVariant defaultValue, QString description)
    : QObject{parent}, key(key), defaultvalue(defaultValue), description(description), type(type)
{
    //logging
    qDebug() << "[EXECDARGUMENT] Key: " << key << ", defaults: " << defaultValue << ", description: " << description;
    m_value = defaultValue;
}
