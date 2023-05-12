#pragma once

#include <Definitions>
#include <cstdint>

namespace Map
{
    //! @struct Стуктура заголовка метаданных РЛИ. Сериализована в Big endian.
    struct ImageMetaHeader
    {
        uint8_t JPEG_HEADER_SIZE = 20;          //! @variable Размер заголовка JPEG до начала метаданных.
        uint16_t meta_marker = 0xFFE1;          //! @variable Маркер начала метаданных. Big-endian.
        uint16_t meta_size;                     //! @variable Размер метаданных. Big-endian.
    };

    //! @struct Стуктура метаданных РЛИ. Сериализована в Little endian.
    struct ImageMetadata
    {
        double latitude = 0;                    //! @variable Широта БПЛА в момент съемки в градусах.
        double longitude = 0;                   //! @variable Долгота БПЛА в момент съемки в градусах.
        float dx = 0;                           //! @variable Шаг по горизонтальной дальности в м/пиксель.
        float dy = 0;                           //! @variable Шаг по путевой дальности в м/пиксель.
        float x0 = 0;                           //! @variable Ближняя граница по горизонтальной дальности в м.
        float y0 = 0;                           //! @variable Смещение кадра по путевой дальности в м.
        float angle = 0;                        //! @variable Путевой азимут в градусах.
        float drift_angle = 0;                  //! @variable Угол сноса отн. путевого угла в градусах.
        float lx = 0;                           //! @variable Размер РЛИ по горизонтали в пикселях.
        float ly = 0;                           //! @variable Размер РЛИ по вертикали в пикселях.
        float div = 0;                          //! @variable Ширина диаграммы направленности антенны.
        float velocity = 0;                     //! @variable Скорость БПЛА в момент съемки в м/с.
        float altitude = 0;                     //! @variable Высота БПЛА отн. уровня моря в момент съемки в м.
        float kr = 0;                           //! @variable Коэффициент частотной интерполяции.
        float time_shift = 0;                   //! @variable Время сдвига в с.
        float time_duration = 0;                //! @variable Время синтезирования в с.
        __reserved float reserved_1 = 0;
        __reserved float reserved_2 = 0;
        uint8_t mode = 0;                       //! @variable Режим съемки.
        uint8_t image_type = 0;                 //! @variable Тип РЛИ (0 - телескопическое).
        __reserved uint32_t reserved_3 = 0;
        __reserved uint32_t reserved_4 = 0;
        uint16_t crc16 = 0;                     //! @variable Контрольная сумма CRC16.
    };
} // namespace Map;
