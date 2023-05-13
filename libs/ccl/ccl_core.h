#pragma once

#include "ccl_global.h"
#include <QtCore/QString>
#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>

namespace ccl
{
    //= Networking =

    CCL_CORE_EXPORT uint32_t ipAddressToHex(const QString& ip_address) noexcept;

    //= Crypto =

    /*!
     * @brief Вычисляет контрольную сумму CRC16 из данных указанного размера
     * @param data - указатель на данные
     * @param size - размер данных для вычисления
     * @return CRC16 выбранных данных !*/
    CCL_CORE_EXPORT uint16_t crc16(char* data, int size) noexcept;

    /*!
    * @brief Вычисляет контрольную сумму CRC16 по алгоритму CCITT из данных указанного размера
    * @param data - указатель на данные
    * @param size - размер данных для вычисления
    * @return CRC16 выбранных данных по алгоритму CCITT !*/
    CCL_CORE_EXPORT uint16_t crc16_ccitt(const char* data, int size) noexcept;

    //= Utility =

    //! @brief Конвертирует QString в C-string
    CCL_CORE_EXPORT char* str_data(const QString& str) noexcept;

    //! @brief Возвращает случайное целочисленное значение в указанном диапазоне
    CCL_CORE_EXPORT int randint_in_range(int range_min, int range_max) noexcept;

    //= Math =

    /*!
     * @brief Вычисляет логарифм по заданному основанию
     * @return Логарифм по основанию base от числа value !*/
    CCL_CORE_EXPORT double logf(double base, double value) noexcept;


    //! @brief Переводит градусы в радианы
    CCL_CORE_EXPORT double deg2rad(double degrees) noexcept;

    //! @brief Переводит радианы в градусы
    CCL_CORE_EXPORT double rad2deg(double radians) noexcept;

    //= Carthography

    /*!
     * @brief  Конвертирует географические градусы в метры
     * @warning Не учитывает текущую широту !*/
    CCL_CORE_EXPORT double geo2meters(double degrees) noexcept;

    /*!
     * @brief  Конвертирует метры в географические градусы
     * @warning Не учитывает текущую широту !*/
    CCL_CORE_EXPORT double meters2geo(double meters) noexcept;

    /*!
    * @brief Возвращает такое значение свойства zoomLevel у MapQuickItem,
    *        что при данных аргументах один пиксель source у MQI будет
    *        равен соотношению meters_per_pixel
    * @param latitude - широта, на которой происходит вычисление
    * @param meters_per_px - количество метров на один экранный пиксель. По умолчанию равно 1
    * @return Значение zoomLevel !*/
    CCL_CORE_EXPORT double mqi_zoom_level(double latitude, float meters_per_pixel = 1) noexcept;

    /*!
    * @brief  Конвертирует геокоординаты в координаты WebMercator
    * @param      QGeoCoordinate point - географические координаты
    * @param      uint8_t zoom - QtLocation::zoomLevel. По умолчанию 19
    * @return     Точка в координатах WebMercator !*/
    CCL_CORE_EXPORT QPointF geo2webmercator(const QGeoCoordinate& geo, uint8_t zoom = 19) noexcept;
}

