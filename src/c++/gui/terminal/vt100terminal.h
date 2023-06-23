#pragma once

#include "terminalbase.h"

namespace GUI
{
  class VT100Terminal : public TerminalBase
  {
    Q_OBJECT

    public:
      static VT100Terminal* get();

    private:
      explicit VT100Terminal(QObject* parent = nullptr);
      VT100Terminal(const VT100Terminal&);
      VT100Terminal& operator=(const VT100Terminal&);
  };
} // GUI

