/**
 *  \file CSARMessage.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <utility>

#include "IO/IMessage.h"

namespace QuasarSDK::IO
{
  /// \brief Класс, реализующий базовое сообщение от РЛС.
  class SARMessage : public IMessage
  {
    public:
      explicit SARMessage();
      explicit SARMessage(QString msg, MessageType t = MessageType::Debug);

      [[nodiscard]] QString message() const override;
      void setMessage(const QString& msg) override;

      [[nodiscard]] MessageType type() const override;
      void setType(MessageType t) override;

    private:
      QString m_message;
      MessageType m_type;
  };

  /**
   * \brief Создает пустое сообщение с типом MessageType::Debug.
   */
  inline SARMessage::SARMessage()
    : m_message(QString())
    , m_type(Debug)
  {}

  /**
   * \brief Создает сообщение с заданными параметрами.
   * \param msg - содержимое сообщения.
   * \param t - тип сообщения.
   */
  inline SARMessage::SARMessage(QString msg, IMessage::MessageType t)
    : m_message(std::move(msg))
    , m_type(t)
  {}

  QString SARMessage::message() const { return m_message; }
  void SARMessage::setMessage(const QString& msg) { m_message = msg; }

  IMessage::MessageType SARMessage::type() const { return m_type; }
  void SARMessage::setType(IMessage::MessageType t) { m_type = t; }
} // QuasarSDK::IO