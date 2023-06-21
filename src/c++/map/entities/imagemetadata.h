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
        uint8_t JPEG_HEADER_SIZE = 20;          //! <@brief Размер заголовка JPEG до начала метаданных.
        uint16_t meta_marker = 0xFFE1;          //! <@brief Маркер начала метаданных. Big-endian.
        uint16_t meta_size;                     //! <@brief Размер метаданных. Big-endian.
    };

    /*!
     *  @brief Тело метаданных телескопического РЛИ.
     *  @details Сериализована в Little Endian.
     */
    struct ImageMetadata
    {
        double latitude = 0;                    //! <@brief Широта БПЛА в момент съемки в градусах.
        double longitude = 0;                   //! <@brief Долгота БПЛА в момент съемки в градусах.
        float dx = 0;                           //! <@brief Шаг по горизонтальной дальности в м/пиксель.
        float dy = 0;                           //! <@brief Шаг по путевой дальности в м/пиксель.
        float x0 = 0;                           //! <@brief Ближняя граница по горизонтальной дальности в м.
        float y0 = 0;                           //! <@brief Смещение кадра по путевой дальности в м.
        float angle = 0;                        //! <@brief Путевой азимут в градусах.
        float drift_angle = 0;                  //! <@brief Угол сноса отн. путевого угла в градусах.
        float lx = 0;                           //! <@brief Размер РЛИ по горизонтали в пикселях.
        float ly = 0;                           //! <@brief Размер РЛИ по вертикали в пикселях.
        float div = 0;                          //! <@brief Ширина диаграммы направленности антенны.
        float velocity = 0;                     //! <@brief Скорость БПЛА в момент съемки в м/с.
        float altitude = 0;                     //! <@brief Высота БПЛА отн. уровня моря в момент съемки в м.
        float kr = 0;                           //! <@brief Коэффициент частотной интерполяции.
        float time_shift = 0;                   //! <@brief Время сдвига в с.
        float time_duration = 0;                //! <@brief Время синтезирования в с.
        float reserved_1 = 0;                   //! <@brief Зарезервированно.
        float reserved_2 = 0;                   //! <@brief Зарезервированно.
        uint8_t mode = 0;                       //! <@brief Режим съемки.
        uint8_t image_type = 0;                 //! <@brief Тип РЛИ (0 - телескопическое).
        uint32_t reserved_3 = 0;                //! <@brief Зарезервированно.
        uint32_t reserved_4 = 0;                //! <@brief Зарезервированно.
        uint16_t crc16 = 0;                     //! <@brief Контрольная сумма CRC16.
    };

    //! @brief Заголовок пакета полосового РЛИ.
    struct StripHeaderMetadata
    {
        uint16_t marker = 0;                    //! <@brief
        uint16_t version = 0;                   //! <@brief
        uint16_t size = 0;                      //! <@brief
        uint16_t cnt = 0;                       //! <@brief
        uint16_t id = 0;                        //! <@brief
        uint16_t type = 0;                      //! <@brief
    } __attribute__((packed));

    //! @brief Навигационные данные пакета полосового РЛИ.
    struct StripNavigationMetadata
    {
        float pitch = 0;                        //! <@brief Тангаж в градусах.
        float roll = 0;                         //! <@brief Крен в градусах.
        float elevation = 0;                    //! <@brief Высота БПЛА (в метрах).
        double latitude = 0;                    //! <@brief
        double longitude = 0;                   //! <@brief
        float velocity = 0;                     //! <@brief Скорость БПЛА в м/с.
        float course = 0;                       //! <@brief Курс БПЛА в градусах.
        float track_ang = 0;                    //! <@brief Сумма курса БПЛА и угла сноса (в градусах).
    } __attribute__((packed));

    //! @brief Данные форматирования пакета полосового РЛИ.
    struct StripFormatMetadata
    {
        float dx = 0;                           //! <@brief
        float dy = 0;                           //! <@brief
        float course = 0;                       //! <@brief
        float roll = 0;                         //! <@brief
        float x0 = 0;                           //! <@brief
        uint8_t word_size = 0;                  //! <@brief
        uint8_t polrization = 0;                //! <@brief
        int16_t y = 0;                          //! <@brief
        uint16_t nx = 0;                        //! <@brief
        uint16_t ny = 0;                        //! <@brief
        float k = 0;                            //! <@brief
    } __attribute__((packed));
} // namespace Map;
