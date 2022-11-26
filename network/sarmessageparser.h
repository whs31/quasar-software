#ifndef SARMESSAGEPARSER_H
#define SARMESSAGEPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

enum DataType : short int
{
    Unrecognized,
    Telemetry
};

class SARMessageParser : public QObject
{
    Q_OBJECT
public:
    explicit SARMessageParser(QObject *parent = nullptr);

    static QString REQUEST_TELEMETRY;

    static DataType checkReceivedDataType(QByteArray data);
    static std::array<double, 5> parseTelemetry (QByteArray data);


signals:

};

#endif // SARMESSAGEPARSER_H
