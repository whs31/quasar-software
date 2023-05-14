#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include "execdargument.h"

#define execd_string execdargument_t::String
#define execd_int execdargument_t::Integer
#define execd_float execdargument_t::Float

class ExecdCommandFormer : public QObject
{
    Q_OBJECT

    public:
        explicit ExecdCommandFormer(QObject* parent = nullptr);

        signals:

    private:
        const QMap<QString, execdargument_t> defaults =
        {
            {"filename", execdargument_t("-f", execd_string, "m1", "Имя файла")},
            {"form_mode", execdargument_t("-m", execd_int, 1, "Режим формирования РЛИ")},
                {"timeshift", execdargument_t("-t", execd_float, 1, "Смещение по времени, с")},
                {"brightness", execdargument_t("-b", execd_int, 0, "Яркость РЛИ")},
                {"sea_level", execdargument_t("--e0", execd_int, 120, "Начальная высота в точке старта")},
//                {"altitude", execdargument_t("-e", execd_int, )},
//                {"velocity", execdargument_t("-v", execd_float)},
//                {"window_function", execdargument_t("-w", execd_string)},
//                {"interpolation", execdargument_t("-i", execd_int)},
//                {"synthesis_time", execdargument_t("--Ts", execd_float)},
//                {"strip_time", execdargument_t("--Tstrip", execd_float)},
//                {"frequency_interpolation_x", execdargument_t("--kR", execd_int)},
//                {"frequency_interpolation_y", execdargument_t("--kL", execd_int)},
//                {"jpeg_quality", execdargument_t("--jq", execd_int)},

//                {"dx", execdargument_t("--dx", execd_float)},
//                {"dy", execdargument_t("--dy", execd_float)},
//                {"x0", execdargument_t("--x0", execd_int)},
//                {"y0", execdargument_t("--y0", execd_int)},
//                {"lx", execdargument_t("--lx", execd_int)},
//                {"ly", execdargument_t("--ly", execd_int)},
//                {"remote_directory", execdargument_t("--ip", execd_string)},
//                {"im", execdargument_t("--im", execd_string)},
//                {"timeshift2", execdargument_t("--Tshift", execd_float)},
//                {"remote_address", execdargument_t("--remote", execd_string)},
//                {"record_duration", execdargument_t("--td", execd_int)},

//                {"focus_rect_x", execdargument_t("--px", execd_float)},
//                {"focus_rect_y", execdargument_t("--py", execd_float)},
//                {"focus_rect_size", execdargument_t("--ls", execd_float)},
//                {"focus_time", execdargument_t("--Ts", execd_float)},
//                {"focus_velocity", execdargument_t("-v", execd_float)},
//                {"focus_velocity_min", execdargument_t("--vmin", execd_float)},
//                {"focus_velocity_max", execdargument_t("--vmax", execd_float)},
//                {"focus_drift_angle", execdargument_t("--driftAngle", execd_float)},
//                {"focus_image_count", execdargument_t("--ni", execd_int)},
        };
};

