#include "config.h"

Config::Config(QString fn) : QSettings(fn, QSettings::IniFormat)
{
    group_t general;
    general["sudo_password"] = "123";
    general["enable_debug_console"] = "true";
    checkValuesSimple(general);

    group_t network;
    network["protocol"] = "UDP";
    network["de10_ip"] = "127.0.0.1";
    network["telemetry_port"] = "25565";
    network["telemetry_update_time"] = "0.2";
    network["computer_ip"] = "127.0.0.1";
    network["image_loader_port"] = "25555";
    network["execd_port"] = "9845";
    network["terminal_port"] = "9846";
    network["use_old_execd_endline"] = "true";
    checkValuesSimple(network);

    group_t map;
    map["use_online_maps"] = "true";
    map["velocity_vector_length"] = "0.2";
    map["antenna_position"] = "r";
    map["diagram_theta_azimuth"] = "20";
    map["previous_session_latitude"] = "60";
    map["previous_session_longitude"] = "30";
    checkValuesSimple(map);

    group_t image;
    image["angle_predefined_correction"] = "0.0";
    image["angle_use_radians_globally"] = "true";
    image["angle_use_drift_angle"] = "true";
    image["angle_theta_azimuth_correction"] = "5.0";
    image["view_mode_default_directory"] = "C:/";
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
