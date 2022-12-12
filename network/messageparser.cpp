/* <Класс MessageParser : QObject>
 *      Класс, содержащий статические методы и переменные
 *      для работы с данными, передаваемыми между ПО и РЛС.
 *      Класс не требует вызова конструктора для работы.
 *
 *•Публичные статические методы:
 *      ► DataType checkReceivedDataType(QByteArray data)
 *
 *        Анализирует массив байтов data и возвращает enum DataType : short int,
 *        равный типу данных, закодированных в массиве байтов.
 *
 *      ► std::array<double, 5> parseTelemetry(QByteArray data)
 *
 *        Принимает массив байтов с телеметрией в формате JSON и возвращает
 *        массив double с данными телеметрии в следующем порядке:
 *        широта, долгота, скорость, высота, количество спутников GPS.
 *
 *•Публичные статические значения:
 *      ► QString REQUEST_TELEMETRY

 *        Строка, на которую откликается сервер и передает данные телеметрии.
*/
#include "messageparser.h"


QString MessageParser::REQUEST_TELEMETRY = "$JSON";
QString MessageParser::REQUEST_FORM = "$FORM";

size_t MessageParser::formMessageID = 0;
MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{

}

DataType MessageParser::checkReceivedDataType(QByteArray data)
{
    QString dts = data.data();
    if(dts.startsWith(MessageParser::REQUEST_TELEMETRY))
        return DataType::Telemetry;
    if(dts.contains("|") && !dts.contains(MessageParser::REQUEST_FORM))
        return DataType::FormResponse;
    return DataType::Unrecognized;
}
std::array<double, 5> MessageParser::parseTelemetry(QByteArray data)
{
    QString dts = data.data();
    dts.remove(0, MessageParser::REQUEST_TELEMETRY.length());

    QJsonDocument jsonDocument = QJsonDocument::fromJson(dts.toUtf8());
    double lat =  jsonDocument.object().value("Latitude").toDouble();
    double lon =  jsonDocument.object().value("Longitude").toDouble();
    double spd =  jsonDocument.object().value("Speed").toDouble();
    double elv =  jsonDocument.object().value("Elevation").toDouble();
    double sats =  jsonDocument.object().value("Sats").toDouble();
    return { lat, lon, spd, elv, sats };
}

QByteArray MessageParser::makeFormRequest(short arg1, short arg2)
{
    QString formRequest = ":";

    QString messageID;
    (formMessageID < 10000) ? formMessageID++ : formMessageID == 1;
    if(formMessageID < 1000)
        messageID = "0";
    if(formMessageID < 100)
        messageID.append("0");
    if(formMessageID < 10)
        messageID.append("0");
    messageID.append(QString::number(formMessageID));
    formRequest.append(messageID + "|");

    QString _formRequest = REQUEST_FORM + "(arg1=" + QString::number(arg1) + ",arg2=" + QString::number(arg2) + ")";
    short strlen = _formRequest.length();
    QString hexlen;
    hexlen.setNum(strlen, 16);
    formRequest.append(hexlen + "|");
    formRequest.append(_formRequest + "|");

    uint16_t crc16 = SChecksum::calculateCRC16(SChecksum::toCharPointer(formRequest), formRequest.length());
    formRequest.append(QString::number(crc16, 16) + "\n");

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
