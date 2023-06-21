#pragma once

#include <cstdint>

//! @brief Пространство имен для классов и функций, связанных с картографией.
namespace Map
{
    /*!
     *  @brief Заголовок метаданных телескопического РЛИ.
     *  @details Сериализована в Big Endian.
     */
    struct ImageMetaHeader
    {
        uint8_t JPEG_HEADER_SIZE = 20;          //! <@var Размер заголовка JPEG до начала метаданных.
        uint16_t meta_marker = 0xFFE1;          //! <@var Маркер начала метаданных. Big-endian.
        uint16_t meta_size;                     //! <@var Размер метаданных. Big-endian.
    };

    /*!
     *  @brief Тело метаданных телескопического РЛИ.
     *  @details Сериализована в Little Endian.
     */
    struct ImageMetadata
    {
        double latitude = 0;                    //! <@var Широта БПЛА в момент съемки в градусах.
        double longitude = 0;                   //! <@var Долгота БПЛА в момент съемки в градусах.
        float dx = 0;                           //! <@var Шаг по горизонтальной дальности в м/пиксель.
        float dy = 0;                           //! <@var Шаг по путевой дальности в м/пиксель.
        float x0 = 0;                           //! <@var Ближняя граница по горизонтальной дальности в м.
        float y0 = 0;                           //! <@var Смещение кадра по путевой дальности в м.
        float angle = 0;                        //! <@var Путевой азимут в градусах.
        float drift_angle = 0;                  //! <@var Угол сноса отн. путевого угла в градусах.
        float lx = 0;                           //! <@var Размер РЛИ по горизонтали в пикселях.
        float ly = 0;                           //! <@var Размер РЛИ по вертикали в пикселях.
        float div = 0;                          //! <@var Ширина диаграммы направленности антенны.
        float velocity = 0;                     //! <@var Скорость БПЛА в момент съемки в м/с.
        float altitude = 0;                     //! <@var Высота БПЛА отн. уровня моря в момент съемки в м.
        float kr = 0;                           //! <@var Коэффициент частотной интерполяции.
        float time_shift = 0;                   //! <@var Время сдвига в с.
        float time_duration = 0;                //! <@var Время синтезирования в с.
        float reserved_1 = 0;                   //! <@var Зарезервированно.
        float reserved_2 = 0;                   //! <@var Зарезервированно.
        uint8_t mode = 0;                       //! <@var Режим съемки.
        uint8_t image_type = 0;                 //! <@var Тип РЛИ (0 - телескопическое).
        uint32_t reserved_3 = 0;                //! <@var Зарезервированно.
        uint32_t reserved_4 = 0;                //! <@var Зарезервированно.
        uint16_t crc16 = 0;                     //! <@var Контрольная сумма CRC16.
    };

    //! @brief Заголовок пакета полосового РЛИ.
    struct StripHeaderMetadata
    {
        uint16_t marker = 0;                    //! <@var
        uint16_t version = 0;                   //! <@var
        uint16_t size = 0;                      //! <@var
        uint16_t cnt = 0;                       //! <@var
        uint16_t id = 0;                        //! <@var
        uint16_t type = 0;                      //! <@var
    } __attribute__((packed));

    //! @brief Навигационные данные пакета полосового РЛИ.
    struct StripNavigationMetadata
    {
        float pitch = 0;                        //! <@var Тангаж в градусах.
        float roll = 0;                         //! <@var Крен в градусах.
        float elevation = 0;                    //! <@var Высота БПЛА (в метрах).
        double latitude = 0;                    //! <@var
        double longitude = 0;                   //! <@var
        float velocity = 0;                     //! <@var Скорость БПЛА в м/с.
        float course = 0;                       //! <@var Курс БПЛА в градусах.
        float track_ang = 0;                    //! <@var Сумма курса БПЛА и угла сноса (в градусах).
    } __attribute__((packed));

    //! @brief Данные форматирования пакета полосового РЛИ.
    struct StripFormatMetadata
    {
        float dx = 0;                           //! <@var
        float dy = 0;                           //! <@var
        float course = 0;                       //! <@var
        float roll = 0;                         //! <@var
        float x0 = 0;                           //! <@var
        uint8_t word_size = 0;                  //! <@var
        uint8_t polrization = 0;                //! <@var
        int16_t y = 0;                          //! <@var
        uint16_t nx = 0;                        //! <@var
        uint16_t ny = 0;                        //! <@var
        float k = 0;                            //! <@var
    } __attribute__((packed));
} // namespace Map;
