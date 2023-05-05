#pragma once

#include <Definitions>
#include "imagemetadata.h++"
#include <QtCore/QString>
#include <QPair>

typedef QPair<QString, QString> image_file_t;

namespace Map
{
    struct Image
    {
        Image();

        ImageMetaHeader header;
        ImageMetadata meta;
        image_file_t path;
    };
} // namespace Map;

