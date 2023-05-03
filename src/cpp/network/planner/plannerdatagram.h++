#pragma once

#include <definitions.h++>
#include <cstdint>
#include <QtCore/QDataStream>

/*                                          Создание полетного задания
            Для создания полетного задания необходимо передать сервису сообщение, которое состоит из заголовка и данных.

            Заголовок
            Заголовок сообщения имеет следующую структуру:

            struct Point{
                uint32_t marker;
                uint16_t id;
                uint16_t r;
                uint32_t ip;
                uint16_t port;
                double lat;
                double lon;
                uint16_t cnt;
                uint16_t len;
            };
            где:
            •	marker - Константа, маркер сообщения. Всегда равен 0x55DD55DD;
            •	id - идентификационный номер точки. Номер должен быть уникален для каждого нового объекта.
                В случае, если послать несколько сообщений с одним и тем же номером, то сообщения будут перезаписаны.
                Может принимать следующие значения: 0..65535;
            •	r - радиус зоны, при достижении которой происходит событие (далее - зона события). Может принимать следующие значения: 0..65535 метров;
            •	ip - IP-адресс (протокол IPv4) для обратной связи в бинарном виде. Например, ip 192.168.1.1 = 0xC0A80101;
            •	port - порт IP-адреса дляобратной связи. Может принимать следующие значения: 0..65535;
            •	lat - географическая широта центра зоны события. Стандарт WGS-84. Может принимать следующие значения: -90..90 градусов;
            •	lon - географическая долгота центра зоны события. Стандарт WGS-84. Может принимать следующие значения: -180..180 градусов;
            •	cnt - время жизни зоны события (в количестве срабатываний при достижении). Может принимать следующие значения: 0..65535;
            •	len - количество байт данных.

            Данные
            Данные должны располагаться сразу же после заголовка. Данные должны быть представлены в виде строки в формате execd
            (без id, размера и контрольной суммы). Например, $some_script(arg1, arg2, arg3)
            Параметр len примера равен 30.

            Удаление точки
            Точки удаляются автоматически при достижении cnt = 0;
            При очередном достижении зоны события счетчик cnt декрементируется.
            Для ручного удаления точки необходимо передать сообщение со следующи заголовком:

            struct Point{
                uint32_t marker = 0x55DD55DD;
                uint16_t id = id удаляемой точки;
                uint16_t r = не имеет значения;
                double lat = не имеет значения;
                double lon = не имеет значения;
                uint16_t cnt = 0;
                uint16_t len = не имеет значения;
            };

            Обратная связь
            При достижении зоны события сервис отправляет сообщение по адресу, указанному при добавлнии точки. Сообщение имеет следующую структуру:

            struct PointResponse{
                uint32_t marker;
                uint16_t id;
                uint16_t cnt;
            };
            где:
            •	marker - Константа, маркер сообщения. Всегда равен 0x55CC55CC;
            •	id - идентификационный номер точки;
            •	cnt - актуальное значение счетчика событий.
 *
*/

namespace Network
{
    struct PlannerAppendDatagram
    {
        uint32_t marker;
        uint16_t id;
        uint16_t r;
        uint32_t ip;
        uint16_t port;
        double lat;
        double lon;
        uint16_t cnt;
        uint16_t len;

        friend QDataStream& operator << (QDataStream& dataStream, const PlannerAppendDatagram& data);
        friend QDataStream& operator >> (QDataStream& dataStream, PlannerAppendDatagram& data);
    };

    struct PlannerRemoveDatagram
    {
        uint32_t marker = 0x55DD55DD;
        uint16_t id;
        uint16_t r;
        double lat;
        double lon;
        uint16_t cnt;
        uint16_t len;

        friend QDataStream& operator << (QDataStream& dataStream, const PlannerRemoveDatagram& data);
        friend QDataStream& operator >> (QDataStream& dataStream, PlannerRemoveDatagram& data);
    };

    struct PlannerResponseDatagram
    {
        uint32_t marker;
        uint16_t id;
        uint16_t cnt;

        friend QDataStream& operator << (QDataStream& dataStream, const PlannerResponseDatagram& data);
        friend QDataStream& operator >> (QDataStream& dataStream, PlannerResponseDatagram& data);
    };

    inline QDataStream &operator << (QDataStream &dataStream, const PlannerAppendDatagram &data)
    {
        dataStream << data.marker;
        dataStream << data.id;
        dataStream << data.r;
        dataStream << data.ip;
        dataStream << data.port;
        dataStream << data.lat;
        dataStream << data.lon;
        dataStream << data.cnt;
        dataStream << data.len;

        return dataStream;
    }

    inline QDataStream &operator >> (QDataStream &dataStream, PlannerAppendDatagram &data)
    {
        dataStream >> data.marker;
        dataStream >> data.id;
        dataStream >> data.r;
        dataStream >> data.ip;
        dataStream >> data.port;
        dataStream >> data.lat;
        dataStream >> data.lon;
        dataStream >> data.cnt;
        dataStream >> data.len;

        return dataStream;
    }

    inline QDataStream &operator <<(QDataStream &dataStream, const PlannerRemoveDatagram &data)
    {
        dataStream << data.marker;
        dataStream << data.id;
        dataStream << data.r;
        dataStream << data.lat;
        dataStream << data.lon;
        dataStream << data.cnt;
        dataStream << data.len;

        return dataStream;
    }

    inline QDataStream &operator >>(QDataStream &dataStream, PlannerRemoveDatagram &data)
    {
        dataStream >> data.marker;
        dataStream >> data.id;
        dataStream >> data.r;
        dataStream >> data.lat;
        dataStream >> data.lon;
        dataStream >> data.cnt;
        dataStream >> data.len;

        return dataStream;
    }

    inline QDataStream &operator <<(QDataStream &dataStream, const PlannerResponseDatagram &data)
    {
        dataStream << data.marker;
        dataStream << data.id;
        dataStream << data.cnt;

        return dataStream;
    }

    inline QDataStream &operator >>(QDataStream &dataStream, PlannerResponseDatagram &data)
    {
        dataStream >> data.marker;
        dataStream >> data.id;
        dataStream >> data.cnt;

        return dataStream;
    }
} // namespace Network;
