#pragma once

#include <cstdint>
#include <QtCore/QDataStream>

/*  Создание полетного задания. Cм. PlannerAppendDatagram.
    Для создания полетного задания необходимо передать сервису сообщение, которое состоит из заголовка и данных.
    Данные должны располагаться сразу же после заголовка. Данные должны быть представлены в виде строки в формате execd

    Удаление точки. См. PlannerRemoveDatagram.
    Точки удаляются автоматически при достижении cnt = 0;
    При очередном достижении зоны события счетчик cnt декрементируется.
    Для ручного удаления точки необходимо передать PlannerRemoveDatagram.

    Обратная связь. См. PlannerResponseDatagram.
    При достижении зоны события сервис отправляет сообщение по адресу, указанному при добавлении точки.
*/

namespace Networking
{
  //! @brief Структура добавления точки в полётное задание. Сериализована в Big Endian.
  struct PlannerAppendDatagram
  {
    uint32_t marker;    //!< Маркер датаграмы. Всегда равен 0x55DD55DD.
    uint16_t id;        //!< Номер точки для планировщика от 0 до \c UINT16_MAX. Точка будет перезаписана, если номер не уникален.
    uint16_t r;         //!< Радиус зоны, в которой будет срабатывать задание планировщика (в м).
    uint32_t ip;        //!< IP-адрес для обратной связи в hex-виде.
    uint16_t port;      //!< Порт для обратной связи.
    double lat;         //!< Широта точки в WGS-84 (в градусах).
    double lon;         //!< Долгота точки в WGS-84 (в градусах).
    uint16_t cnt;       //!< Количество срабатывания события в точке перед ее удалением от 0 до \c UINT16_MAX.
    uint16_t len;       //!< Количество байт в #command.
    QByteArray command; //!< Команда для выполнения в точке в формате \b execd.
    // $some_script(arg1, arg2, arg3)  ; для этой команды len = 30.

    friend QDataStream& operator << (QDataStream& dataStream, const PlannerAppendDatagram& data);
    friend QDataStream& operator >> (QDataStream& dataStream, PlannerAppendDatagram& data);
  };

  //! @brief Структура удаления точки из полётного задания. Сериализована в Big Endian.
  struct PlannerRemoveDatagram
  {
    uint32_t marker;    //!< Маркер датаграмы. Всегда равен \c 0x55DD55DD.
    uint16_t id;        //!< Номер точки для удаления.
    uint16_t r = 0;     //!< Всегда равен 0.
    double lat = 0;     //!< Всегда равен 0.
    double lon = 0;     //!< Всегда равен 0.
    uint16_t cnt = 0;   //!< Всегда равен 0.
    uint16_t len = 0;   //!< Всегда равен 0.

    friend QDataStream& operator << (QDataStream& dataStream, const PlannerRemoveDatagram& data);
    friend QDataStream& operator >> (QDataStream& dataStream, PlannerRemoveDatagram& data);
  };

  //! @brief Структура ответа на прохождение БПЛА через точку из полётного задания. Сериализована в Big Endian.
  struct PlannerResponseDatagram
  {
    uint32_t marker;    //!< Маркер датаграмы. Всегда равен \c 0x55CC55CC.
    uint16_t id;        //!< Номер точки.
    uint16_t cnt;       //!< Актуальное значение счетчика времени жизни точки.

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
    dataStream << data.command;

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
    dataStream >> data.command;

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
