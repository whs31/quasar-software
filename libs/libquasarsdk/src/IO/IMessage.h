/**
 *  \file IMessage.h
 *  \author Дмитрий Рязанцев
 *  \date 08.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QString>

namespace QuasarSDK::IO
{
  /**
   * \brief Интерфейс, описывающий консольное сообщение.
   */
  class IMessage
  {
    public:
      /**
       * \brief Перечисление типов сообщения.
       * \details Содержит базовые типы сообщения.
       * Перечисление можно расширить в классах-имплементациях этого интерфейса.
       * Для этого необходимо описать новое перечисление, в котором первое значение будет равняться
       * <tt>IMessage::MessageType + 1</tt>. Пример:
       * \code {.cpp}
            class CriticalMessage : public IMessage
            {
                public:
                    enum CriticalMessageType
                    {
                        OutOfMemory = IMessage::MessageType + 1,
                        SegmentationFault,
                        UnhandledException,
                        PermissionDenied
                    };

                    // ...
            };
       * \endcode
       */
      enum MessageType
      {
        Debug,              ///< Отладочное сообщение.
        DebugSpecific,      ///< Особое отладочное сообщение.
        Info,               ///< Информационное сообщение.
        InfoSpecific,       ///< Особое информационное сообщение.
        Warning,            ///< Предупреждение.
        Error,              ///< Ошибка.
        ErrorSpecific,      ///< Особая ошибка (например, критическая).
        UserDefined         ///< Пользовательские типы сообщения.
      };

      [[nodiscard]] virtual QString message() const = 0;      ///< Возвращает строку с сообщением.
      virtual void setMessage(const QString& msg) = 0;        ///< Задает строку с сообщением.

      [[nodiscard]] virtual MessageType type() const = 0;     ///< Возвращает тип сообщения.
      virtual void setType(MessageType t) = 0;                ///< Задает тип сообщения.
  };
} // QuasarSDK::IO

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::IO::IMessage::MessageType)
