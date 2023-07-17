/**
 *  \file CCompleteMapImage.h
 *  \author Дмитрий Рязанцев
 *  \date 12.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/mapimage.h"
#include "IO/draftfile.h"

namespace QuasarSDK::Map
{
  /**
   * \ingroup sdk_images
   * \brief Радиолокационное изображение на карте, сохраненное в файл.
   */
  class CompleteMapImage : public MapImage
                         , public IO::DraftFile
  {
    public:
      /**
       * \brief Создает объект CompleteMapImage со значениями по умолчанию.
       */
      CompleteMapImage();

      /**
       * \brief Создает объект MapImage с указанными значениями.
       * \param filename - имя файла без расширения.
       * \param extension - расширения файла (*без точки*).
       * \param coord - координаты привязки изображение.
       * \param offset - смещение изображение в метрах по осям X и Y (м).
       * \param rect - размер прямоугольника, ограничивающего изображение (м).
       * \param angle - азимутальный угол поворота изображения в градусах от севера.
       * \param dx_ratio - количество метров на один пиксель.
       * \param origin_point - точка привязки (в пикселях).
       */
      CompleteMapImage(const QString& filename, const QString& extension,
                       const QGeoCoordinate& coord, const QPointF& offset, const QSizeF& rect,
                       float angle, float dx_ratio = 1, const QPointF& origin_point = {0, 0});
  };
} // QuasarSDK:: Map
