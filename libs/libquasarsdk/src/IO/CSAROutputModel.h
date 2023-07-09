/**
 *  \file CSARMessageModel.h
 *  \author Дмитрий Рязанцев
 *  \date 09.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "IO/CMessageModel.h"
#include "IO/CSARMessage.h"

namespace QuasarSDK::IO
{
  /**
   * \brief Класс-модель, обрабатывающий и хранящий сообщения от РЛС (*VT100*).
   */
  class SAROutputModel : public MessageModel
  {
    Q_OBJECT

    public:
      explicit SAROutputModel(QObject* parent = nullptr);

      void newline() noexcept;                                  ///< Добавляет пустую строку в модель.
      void print(const QByteArray& data) noexcept;              ///< Обрабатывает VT100-последовательности и добавляет новые строки в модель.

    private:
      [[nodiscard]] QString lastLine() const noexcept;
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