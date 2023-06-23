#include "vt100terminal.h"

namespace GUI
{

  VT100Terminal* VT100Terminal::get() { static VT100Terminal instance; return &instance; }

  VT100Terminal::VT100Terminal(QObject* parent)
    : TerminalBase(parent)
  {}

} // GUI
