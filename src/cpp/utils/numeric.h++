#pragma once

#include <definitions.h++>
#include <QtCore/QObject>
#include <QtCore/QPointF>

class QGeoCoordinate;

//! @namespace Пространство имен для утилит и полезных алгоритмов.
namespace Utilities
{
    //! @class Класс-утилита, содержащий функции для работы с математикой и картографией.
    class Numeric : public QObject
    {
        Q_OBJECT

        //! @variable Константы для конвертации zoomLevel в геометрическое расстояние и обратно.
        constexpr __global double MAP_SCALE_RATIO = 156'543.03392;
        constexpr __global double INVERSE_MAP_SCALE_RATIO = 28.8659;

        //! @variable Константа. Равна количеству километров в одном градусе.
        //! @warning Не учитывает широту.
        constexpr __global double KILOMETERS_IN_DEGREE = 111.111;

        public:
            Numeric(QObject* parent = nullptr);

            //! @brief  Конвертирует географические градусы в километры.
            //! @param      double degrees - градусы.
            //! @return     Расстояние в километрах.
            //! @warning    Не учитывает значение широты.
            __qml static float degreesToKilometers(double degrees) noexcept(true);

            //! @brief  Конвертирует географические градусы в метры.
            //! @param      double degrees - градусы.
            //! @return     Расстояние в метрах.
            //! @warning    Не учитывает значение широты.
            __qml static float degreesToMeters(double degrees) noexcept(true);

            //! @brief  Конвертирует километры в географические градусы.
            //! @param      float meters - метры.
            //! @return     Расстояние в географических градусах.
            //! @warning    Не учитывает значение широты.
            __qml static double metersToDegrees(float meters) noexcept(true);

            //! @brief  Возвращает такое значение QtLocation::zoomLevel, что при данных аргументах один метр
            //!         будет равен meters_per_px (или 1, если не задано) экранному пикселю.
            //! @param      double latitude - широта, на которой происходит вычисление.
            //! @param      float meters_per_px - количество метров на один экранный пиксель. По умолчанию равно 1.
            //! @return     Значение zoomLevel.
            __qml static float mercatorZoomLevel(double latitude, float meters_per_px = 0) noexcept(true);

            //! @brief  Возвращает значение метров на пиксель для текущего zoom_level и широты.
            //! @param      float zoom_level - QtLocation::zoomLevel,
            //! @param      double latitude - широта, на которой происходит вычисление.
            //! @return     Пропорция метры/пиксель для данных аргументов.
            __qml static double zoomLevelToRatio(float zoom_level, double latitude = 0) noexcept(true);

            //! @brief  Переводит градусы в радианы.
            //! @param      float degrees - градусы.
            //! @return     Значение в радианах.
            __qml static float degreesToRadians(float degrees) noexcept(true);

            //! @brief  Переводит радианы в градусы.
            //! @param      float radians - радианы.
            //! @return     Значение в градусах.
            __qml static float radiansToDegrees(float radians) noexcept(true);

            //! @brief  Конвертирует геокоординаты в координаты WebMercator.
            //! @param      QGeoCoordinate point - географические координаты.
            //! @param      uint8_t zoom - QtLocation::zoomLevel. По умолчанию 19.
            //! @return     Точка в координатах WebMercator.
            __qml static QPointF geoCoordToWebMercator(const QGeoCoordinate& point, uint8_t zoom = 19) noexcept(true);
    };
} // namespace Utilities;
