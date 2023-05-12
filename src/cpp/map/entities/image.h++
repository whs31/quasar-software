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

        QString filename;
        ImageMetaHeader header;
        ImageMetadata meta;
        image_file_t path;
        bool valid = false;

        float opacity = 1;
        bool shown = true;
        double mercator_zoom_level;

        friend QDebug& operator<< (QDebug& d, Map::Image& image);
    };
} // namespace Map;

