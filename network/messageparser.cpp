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
MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{

}

DataType MessageParser::checkReceivedDataType(QByteArray data)
{
    QString dts = data.data();
    if(dts.startsWith(MessageParser::REQUEST_TELEMETRY))
    {
        return DataType::Telemetry;
    }
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
