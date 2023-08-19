#pragma once

#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QList>
#include <QtPositioning/QGeoCoordinate>
#include <QuasarSDK/Neural>
#include "imagemetadata.h"

typedef QPair<QString, QString> image_file_t;

namespace Map
{
  struct Image
  {
    QString filename;
    image_file_t path;
    bool valid = false;

    float opacity = 1;
    bool shown = true;
    bool marked_for_export = false;
    double mercator_zoom_level;
    QList<QuasarSDK::NeuralData> neural_data;
  };

  struct TelescopicImage : public Image
  {
    ImageMetaHeader header;
    ImageMetadata meta;
  };

  struct StripImage : public Image
  {
    QGeoCoordinate coordinate;
    float azimuth;
    float lx;
    float ly;
    float dx;
    float offset_x;
    float offset_y;
  };

  struct StripImageDatagram
  {
    StripHeaderMetadata header;
    StripNavigationMetadata nav;
    StripFormatMetadata format;
  };
} // namespace Map;

