#include "vt100parser.h"
#include <QtCore/QRegExp>

Network::utils::vt100_result_t Network::utils::parse_vt100_string(const QString& string)
{
    vt100_result_t ret;
    ret.result = string;

    QRegExp regex("\\033\\[\\d+D");
    if(string.contains(regex))
    {
        ret.result.remove(regex);
        ret.move_up = true;
        ret.return_carriage = true;
    }

    return ret;
}
