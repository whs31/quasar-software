/* <Класс SARMessageParser : QObject>
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

#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    static QStringList parseFormResponse(QByteArray data);
    static QByteArray makeFormRequest(short arg1 = 1, short arg2 = 1);


signals:

private:
    explicit MessageParser(QObject *parent = nullptr);
    static size_t formMessageID;
};

#endif // MESSAGEPARSER_H
