#pragma once

#include "terminalbase.h"

namespace GUI
{
  class VT100Terminal : public TerminalBase
  {
    Q_OBJECT

    public:
      static VT100Terminal* get();

      void newline() noexcept;
      void print(const QByteArray& data) noexcept;

    private:
      explicit VT100Terminal(QObject* parent = nullptr);
      VT100Terminal(const VT100Terminal&);
      VT100Terminal& operator=(const VT100Terminal&);

      [[nodiscard]] QString lastLine() const noexcept; void setLastLine(const QString& str);
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
} // GUI

