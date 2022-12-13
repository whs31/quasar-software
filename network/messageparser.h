#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <cstring>

#include "schecksum.h"

enum DataType : short int
{
    Unrecognized,
    Telemetry,
    FormRequest,
    FormResponse
};

class MessageParser : public QObject
{
    Q_OBJECT
public:
    static QString REQUEST_TELEMETRY;
    static QString REQUEST_FORM;

    static DataType checkReceivedDataType(QByteArray data);
    static DataType checkSendingDataType(QByteArray data);

    static std::array<double, 6> parseTelemetry (QByteArray data);

    static std::array<int, 4> parseFormResponse(QByteArray data);
    static QByteArray makeFormRequest(QString arg1, quint32 arg2, quint32 arg3, float arg4, float arg5, float arg6);


signals:

private:
    explicit MessageParser(QObject *parent = nullptr);
    static size_t formMessageID;
};

#endif // MESSAGEPARSER_H
