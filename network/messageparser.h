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

    static std::array<double, 5> parseTelemetry (QByteArray data);

    static std::array<int, 4> parseFormResponse(QByteArray data);
    static QByteArray makeFormRequest(short arg1 = 1, short arg2 = 1);


signals:

private:
    explicit MessageParser(QObject *parent = nullptr);
    static size_t formMessageID;
};

#endif // MESSAGEPARSER_H
