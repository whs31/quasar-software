#pragma once

#include "imagemetadata.h"
#include <QtCore/QString>
#include <QtCore/QPair>

typedef QPair<QString, QString> image_file_t;

namespace Map
{
    struct StripImage
    {
        QString filename;
        image_file_t path;
        bool valid = false;

        float opacity = 1;
        bool shown = true;
    };

    struct StripImageDatagram
    {
        StripHeaderMetadata header;
        StripNavigationMetadata nav;
        StripFormatMetadata format;
    };
} // namespace Map;
