#pragma once

#include <QtCore/QString>

namespace Networking
{
    namespace utils
    {
        struct vt100_result_t
        {
            QString result;
            bool return_carriage = false;
            bool move_up = false;
        };

        vt100_result_t parse_vt100_string(const QString& string);
    } // utils
} // Network
