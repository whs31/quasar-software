#include "jsonconfig.h"

JsonConfig::JsonConfig(QString filename)
{
    QFile jsonfile(filename);
    if(!QFile::exists(filename))
    {
        jsonfile.open(QIODevice::WriteOnly | QIODevice::Text);
        jsonfile.close();
    }
}
