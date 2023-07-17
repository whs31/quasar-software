/**
 *  \file CBaseUDPSocket.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtNetwork/QUdpSocket>
#include "iconnectable.h"

namespace QuasarSDK
{
  class BaseUDPSocket : public QUdpSocket,
                        public IConnectable
  {
    Q_OBJECT

    public:
      explicit BaseUDPSocket(QObject* parent = nullptr);
      ~BaseUDPSocket() override;

      [[nodiscard]] QString name() const; void setName(const QString&) noexcept;

      void start(const QString& address) override;
      void start(const QHostAddress& address) noexcept final;
      void start(const QHostAddress& address, uint16_t port) noexcept override;

      void stop() noexcept override;

      virtual void send(const QByteArray& data) noexcept;

      [[nodiscard]] QString addressString() const noexcept;
      [[nodiscard]] QHostAddress hostAddress() const noexcept;
      [[nodiscard]] QString hostAddressString() const noexcept;
      [[nodiscard]] uint16_t port() const noexcept;

    signals:
      /// \brief Срабатывает, когда сокет принимает датаграмму.
      void received(QByteArray data);

      /**
       * \brief Предоставляет отладочные метрики сокета.
       * \details Этот сигнал по умолчанию не имеет особой имплементации
       * и срабатывает только при подключении и отключении от адреса.
       * В дочерних классах сигнал может иметь свою имплементацию, например,
       * на прием или отправку данных.
       * Данные предоставлены в сигнале в виде строки для того, чтобы
       * иметь возможность предоставлять отладочную информацию о структурах
       * и бинарных данных, проходящих через сокет. Рекомендуется приводить
       * данные к строке по следующему правилу:
       *    - *строки или текст*: в исходном виде без изменений
       *    - *структуры*: почленно приведенные к строке
       *    - *бинарные данные/большие пакеты*: тип данных с указанием размера (напр. <tt>Data with size of 1024 KB</tt>)
       *
       * \param data - данные, проходящие через сокет, приведенные к строке.
       * \param data_size - размер данных в байтах.
       * \param out - направление потока данных. \c True означает, что данные идут из сокета в целевой адрес.
       */
      void metrics(const QString& data, int data_size, bool out);

    protected:
      Q_SLOT virtual void readSocket() noexcept;

    private:
      QString m_socketname;
      QHostAddress m_address;
      uint16_t m_port;
  };
} // QuasarSDK
