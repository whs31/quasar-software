#include "mapcompleteimage.h"

namespace QuasarSDK::Map
{
  CompleteMapImage::CompleteMapImage()
    : MapImage()
    , IO::DraftFile()
  {}

  CompleteMapImage::CompleteMapImage(const QString& filename, const QString& extension, const QGeoCoordinate& coord,
                                     const QPointF& offset, const QSizeF& rect, float angle, float dx_ratio,
                                     const QPointF& origin_point)
    : MapImage(coord, offset, rect, angle, dx_ratio, origin_point)
    , IO::DraftFile(filename, extension)
  {}
} // QuasarSDK::Map