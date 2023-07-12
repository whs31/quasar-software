/**
 *  \file CMapImageSegment.h
 *  \author Дмитрий Рязанцев
 *  \date 12.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "Map/CMapImage.h"
#include "IO/CBase64Object.h"

namespace QuasarSDK::Map
{
  /**
   * \ingroup sdk_images
   * \brief Сегмент или полное радиолокационное изображение на карте, сохраненное в *Base64*-строке.
   */
  class MapImageSegment : public MapImage
                        , public IO::Base64Object
  {
      /**
       * \brief Создает объект MapImageSegment со значениями по умолчанию.
       */
      MapImageSegment();
  };
} // QuasarSDK:: Map
