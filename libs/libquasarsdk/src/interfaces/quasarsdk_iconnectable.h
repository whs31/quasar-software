/**
 *  \file quasarsdk_iconnectable.h
 *  \author Дмитрий Рязанцев
 *  \date 07.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QString>
#include <QtNetwork/QHostAddress>

namespace QuasarSDK
{
  /**
   * \brief Абстрактный интерфейс для классов с функционалом подключения и отключения к сетевому адресу.
   * \details Обладает функциями start() и stop().
   */
  class IConnectable
  {
    public:
      /**
       * \brief Подключается к указанному адресу в виде строки.
       * \note Предполагается, что эта функция может выбрасывать
       * исключения (например, если предоставленная строка некорректна).
       * \param address - строка с адресом.
       */
      virtual void start(const QString& address) = 0;

      /**
       * \brief Подключается к указанному сетевому адресу (QHostAddress).
       * \param address - сетевой адрес.
       */
      virtual void start(const QHostAddress& address) noexcept = 0;

      /**
       * \brief Подключается к указанной паре из QHostAddress и port.
       * \param address - сетевой адрес.
       * \param port - порт для подключения.
       */
      virtual void start(const QHostAddress& address, uint16_t port) noexcept = 0;

      /// \brief Разрывает существующее соединение.
      virtual void stop() noexcept = 0;
  };
} // QuasarSDK
