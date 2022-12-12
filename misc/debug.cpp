#include "debug.h"

Debug::Debug(QObject *parent)
    : QObject{parent}
{

}

void Debug::Log(QString text)
{
    uint8_t type = 0;
    if(text.startsWith("!!"))
    { type = 3; } else if(text.startsWith("!"))
    { type = 2; } else if(text.startsWith("?"))
    { type = 1; } else if(text.startsWith("!!!"))
    { type = 4; }
    switch (type) {
    case 1: {
        text.remove(0, 1);
        qInfo().noquote().nospace()<<QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss(z)")<<text;
        break;
    }
    case 2: {
        text.remove(0, 1);
        qWarning().noquote().nospace()<<QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss(z)")<<text;
        break;
    }
    case 3: {
        text.remove(0, 2);
        qCritical().noquote().nospace()<<QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss(z)")<<text;
        break;
    }
    case 4: {
        text.remove(0, 3);
        text.prepend(" FATAL ERROR:");
        text.prepend(QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss(z)"));
        QByteArray ba = text.toLocal8Bit();
        const char *c_str2 = ba.data();
        qFatal("%s", c_str2);
        break;
    }
    default: {
        qDebug().noquote().nospace()<<QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss(z)")<<text;
        break;
    }}
}

void Debug::NewSession()
{
    for(short i = 0; i < 15; i++)
    {
        qDebug()<<" ";
    }
    qInfo()<<"=================================NEW SESSION========================================="; 
}