#include "messageparser.h"

QString MessageParser::REQUEST_TELEMETRY = "$JSON";
QString MessageParser::REQUEST_FORM = "$FORM";

size_t MessageParser::formMessageID = 0;
MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{}

DataType MessageParser::checkReceivedDataType(QByteArray data)
{
    QString dts = data.data();
    if(dts.startsWith(MessageParser::REQUEST_TELEMETRY))
        return DataType::Telemetry;
    if(dts.contains("|") && !dts.contains(MessageParser::REQUEST_FORM))
        return DataType::FormResponse;
    return DataType::Unrecognized;
}
QPair<qreal, qint16> MessageParser::parseTelemetry(QByteArray data)
{
    QString dts = data.data();
    dts.remove(0, MessageParser::REQUEST_TELEMETRY.length());

    QJsonDocument jsonDocument = QJsonDocument::fromJson(dts.toUtf8());
    double lat =  jsonDocument.object().value("Latitude").toDouble();
    double lon =  jsonDocument.object().value("Longitude").toDouble();
    double spd =  jsonDocument.object().value("Speed").toDouble();
    double elv =  jsonDocument.object().value("Elevation").toDouble(); 
    double sats =  jsonDocument.object().value("Sats").toDouble(); 
    double direction = jsonDocument.object().value("Direction").toDouble(); //TODO: direction
    RuntimeData::initialize()->setLatitude(lat);
    RuntimeData::initialize()->setLongitude(lon);
    RuntimeData::initialize()->setElevation(elv);
    RuntimeData::initialize()->setSpeed(spd); //TODO: direction
    RuntimeData::initialize()->setSatellites(sats);
    return QPair<qreal, qint16>(lat, sats);
}

QByteArray MessageParser::makeFormRequest(QString arg1, quint32 arg2, quint32 arg3, float arg4, float arg5, float arg6, int arg7, float arg8, float arg9)
{
    QString formRequest = ":" + QStringLiteral("%1").arg(++formMessageID, 4, 10, QLatin1Char('0')) + "|";
    QString _formRequest = REQUEST_FORM + "(" 
                                        + arg1 + ","                            //mode (m1, m2) : QString
                                        + QString::number(arg2) + ","           //x0 : int
                                        + QString::number(arg3) + ","           //lx + x0 : int
                                        + QString::number(arg4, 'f', 1) + ","   //ts : float
                                        + QString::number(arg5, 'f', 1) + ","   //dx : float 
                                        + QString::number(arg6, 'f', 1) + ","   //dy : float (dx = dy in most cases)
                                        + QString::number(arg7) + ","           //override gps data : (int)bool
                                        + QString::number(arg8, 'f', 0) + ","   //height : float
                                        + QString::number(arg9, 'f', 1)         //speed : float 
                                        + ")";
    QString hexlen;
    hexlen.setNum(_formRequest.length(), 16);
    formRequest.append(hexlen + "|" + _formRequest + "|");
    formRequest.append(QStringLiteral("%1").arg(SChecksum::calculateCRC16(SChecksum::toCharPointer(formRequest), formRequest.length()), 4, 16, QLatin1Char('0')));
    if(SConfig::getHashBoolean("UseOldExecdEndline"))
        formRequest.append("\n");
    return formRequest.toUtf8();
}

std::array<int, 4> MessageParser::parseFormResponse(QByteArray data)
{
    QString rawString = data.data();
    QString checkCrc = rawString;
    checkCrc.chop(5);

    QStringList response = rawString.split("|");
    int strlen = response[1].toInt(nullptr, 10);
    response[2].remove(0, 1);

    //crc16
    uint16_t crc16 = SChecksum::calculateCRC16(SChecksum::toCharPointer(checkCrc), checkCrc.length());
    uint16_t receivedCrc16 = response[3].toUInt(nullptr, 16);
    int checksumCheckResult = (crc16 == receivedCrc16) ? 1 : 0;

    return { response[0].toInt(), strlen, response[2].toInt(), checksumCheckResult };
}
