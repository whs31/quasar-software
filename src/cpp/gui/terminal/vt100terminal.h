#pragma once

#include "terminalbase.h"
#include <LPVL/Global>

namespace GUI
{
    class VT100Terminal : public TerminalBase
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(VT100Terminal)

        private:
            VT100Terminal(QObject* parent = nullptr);
    };
} // GUI

