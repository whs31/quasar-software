#include "config.h"

Config::Config(QString fn) : QSettings(fn, QSettings::IniFormat)
{
         /*
         * Заполнять стандартные параметры рекомендуется так:
         * group_t <Название группы>;
         * <Название группы>["<Название параметра>"] = "<Значение>";
         * checkValuesSimple(<Название группы>);
         */

    group_t utility;
    utility["version"] = "1111";
    checkValuesSimple(utility);

    group_t telemetry;
    telemetry["type"] = "UDP";
    telemetry["address"] = "127.0.0.1";
    telemetry["port"] = "25565";
    telemetry["updateTime"] = "0.5";
    checkValuesSimple(telemetry);

    group_t network;
    network["type"] = "TCP";
    network["address"] = "127.0.0.1";
    network["port"] = "25565";
    telemetry["updateTime"] = "0.5";
    checkValuesSimple(network);

    group_t map;
    map["predict_line_range"] = "4";
    map["capture_time"] = "15";
    map["diagram_length"] = "3";
    map["diagram_theta_azimuth"] = "12.5";
    map["diagram_drift_angle"] = "11";
    checkValuesSimple(map);

    group_t image;
    image["show_all_images_on_init"] = "false";
    checkValuesSimple(image);
}

void Config::checkValues(QString group, group_t *list){

    QMapIterator<QString, QString> i(*list);

    beginGroup(group);
    while (i.hasNext()) {
        i.next();
        if(!value(i.key()).isValid()){
            setValue(i.key(), i.value());
        }
    }
    endGroup();
    list->clear();
}
