#pragma once

#include <cstdint>

namespace Map
{
    //! @struct Стуктура заголовка метаданных РЛИ. Сериализована в Big endian.
    struct ImageMetaHeader
    {
        uint8_t JPEG_HEADER_SIZE = 20;          //! @var Размер заголовка JPEG до начала метаданных.
        uint16_t meta_marker = 0xFFE1;          //! @var Маркер начала метаданных. Big-endian.
        uint16_t meta_size;                     //! @var Размер метаданных. Big-endian.
    };

    //! @struct Стуктура метаданных РЛИ. Сериализована в Little endian.
    struct ImageMetadata
    {
        double latitude = 0;                    //! @var Широта БПЛА в момент съемки в градусах.
        double longitude = 0;                   //! @var Долгота БПЛА в момент съемки в градусах.
        float dx = 0;                           //! @var Шаг по горизонтальной дальности в м/пиксель.
        float dy = 0;                           //! @var Шаг по путевой дальности в м/пиксель.
        float x0 = 0;                           //! @var Ближняя граница по горизонтальной дальности в м.
        float y0 = 0;                           //! @var Смещение кадра по путевой дальности в м.
        float angle = 0;                        //! @var Путевой азимут в градусах.
        float drift_angle = 0;                  //! @var Угол сноса отн. путевого угла в градусах.
        float lx = 0;                           //! @var Размер РЛИ по горизонтали в пикселях.
        float ly = 0;                           //! @var Размер РЛИ по вертикали в пикселях.
        float div = 0;                          //! @var Ширина диаграммы направленности антенны.
        float velocity = 0;                     //! @var Скорость БПЛА в момент съемки в м/с.
        float altitude = 0;                     //! @var Высота БПЛА отн. уровня моря в момент съемки в м.
        float kr = 0;                           //! @var Коэффициент частотной интерполяции.
        float time_shift = 0;                   //! @var Время сдвига в с.
        float time_duration = 0;                //! @var Время синтезирования в с.
        float reserved_1 = 0;
        float reserved_2 = 0;
        uint8_t mode = 0;                       //! @var Режим съемки.
        uint8_t image_type = 0;                 //! @var Тип РЛИ (0 - телескопическое).
        uint32_t reserved_3 = 0;
        uint32_t reserved_4 = 0;
        uint16_t crc16 = 0;                     //! @var Контрольная сумма CRC16.
    };

    struct StripNavigationMetadata
    {
        float pitch;                            //! @var
        float roll;                             //! @var
        float elevation;                        //! @var
        double latitude;                        //! @var
        double longitude;                       //! @var
        float velocity;                         //! @var
        float course;                           //! @var
        float track_ang;                        //! @var
    };

    struct StripHeaderMetadata
    {
        uint16_t marker;                        //! @var
        uint16_t version;                       //! @var
        uint16_t size;                          //! @var
        uint16_t cnt;                           //! @var
        uint16_t id;                            //! @var
        uint16_t type;                          //! @var
    };

    struct StripFormatMetadata
    {
        float dx;                               //! @var
        float dy;                               //! @var
        float course;                           //! @var
        float roll;                             //! @var
        float x0;                               //! @var
        uint8_t word_size;                      //! @var
        uint8_t polarization;                   //! @var
        int16_t y;                              //! @var
        uint16_t nx;                            //! @var
        uint16_t ny;                            //! @var
        float k;                                //! @var
    };
} // namespace Map;
