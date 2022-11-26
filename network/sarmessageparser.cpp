#include "sarmessageparser.h"


QString SARMessageParser::REQUEST_TELEMETRY = "$JSON";
SARMessageParser::SARMessageParser(QObject *parent)
    : QObject{parent}
{

}

DataType SARMessageParser::checkReceivedDataType(QByteArray data)
{
    QString dts = data.data();
    if(dts.startsWith(SARMessageParser::REQUEST_TELEMETRY))
    {
        return DataType::Telemetry;
    }
    return DataType::Unrecognized;
}
std::array<double, 5> SARMessageParser::parseTelemetry(QByteArray data)
{
    QString dts = data.data();
    dts.remove(0, SARMessageParser::REQUEST_TELEMETRY.length());

    QJsonDocument jsonDocument = QJsonDocument::fromJson(dts.toUtf8());
    double lat =  jsonDocument.object().value("Latitude").toDouble();
    double lon =  jsonDocument.object().value("Longitude").toDouble();
    double spd =  jsonDocument.object().value("Speed").toDouble();
    double elv =  jsonDocument.object().value("Elevation").toDouble();
    double sats =  jsonDocument.object().value("Sats").toDouble();
    return { lat, lon, spd, elv, sats };
}
