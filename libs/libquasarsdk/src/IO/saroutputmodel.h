/**
 *  \file CSARMessageModel.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IO/messagemodel.h"
#include "IO/sarmessage.h"

namespace QuasarSDK::IO
{
  /**
   * \ingroup sdk_io
   * \ingroup sdk_models
   * \brief Класс-модель, обрабатывающий и хранящий сообщения от РЛС (*VT100*).
   */
  class SAROutputModel : public MessageModel
  {
    Q_OBJECT

    public:
      explicit SAROutputModel(QObject* parent = nullptr);

      void newline();                                  ///< Добавляет пустую строку в модель.
      void print(const QByteArray& data);              ///< Обрабатывает VT100-последовательности и добавляет новые строки в модель.

      /// \brief Выводит в консоль введенную команду.
      Q_INVOKABLE void displayCommand(const QString& command);

    private:
      [[nodiscard]] QString lastLine() const;
      void setLastLine(const QString& str);

      void appendString(const QString& text);

    private:
      enum State
      {
        Text,
        Escape,
        Format,
        ResetFont
      };
      State m_state;
      int m_formatValue;

      struct CursorPosition
      {
        int x;
        int y;
      } m_cursorPosition;
  };
} // QuasarSDK::IO

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::IO::SAROutputModel*)
