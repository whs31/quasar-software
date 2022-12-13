#include "config.h"

Config::Config(QString fn) : QSettings(fn, QSettings::IniFormat)
{
    group_t general;
    general["version"] = "1.2.4alpha";
    general["is_stable"] = "false";
    general["sudo_password"] = "123";
    general["program_mode"] = "true"; //"flight" = true, "view" = false
    checkValuesSimple(general);

    group_t utility;
    utility["use_osm_maps"] = "false";
    utility["display_profiler"] = "false";
    utility["enable_debug_console"] = "true";
    checkValuesSimple(utility);

    group_t network;
    network["core_type"] = "UDP";
    network["sar_ip"] = "127.0.0.1";
    network["telemetry_port"] = "25565";
    network["telemetry_update_time"] = "0.5";
    network["image_loader_ip"] = "127.0.0.1";
    network["image_loader_port"] = "25555";
    network["dialog_port"] = "9845";
    network["console_listen_port"] = "9846";
    checkValuesSimple(network);

    group_t map;
    map["velocity_vector_length"] = "4";
    map["antenna_position"] = "r";
    checkValuesSimple(map);

    group_t diagram;
    diagram["diagram_capture_time"] = "15";
    diagram["diagram_capture_range"] = "3";
    diagram["diagram_theta_azimuth"] = "12.5";
    diagram["diagram_drift_angle"] = "11";
    checkValuesSimple(diagram);

    group_t image;
    image["angle_predefined_correction"] = "0.0";
    image["angle_use_radians_globally"] = "true";
    image["use_base64_encoding_optimization"] = "true";
    image["save_image_only_when_loading_finished"] = "true";
    image["view_mode_default_directory"] = "C:/";
    checkValuesSimple(image);

    group_t startup;
    startup["display_images_when_loaded"] = "true";
    startup["connect_to_sar"] = "false";
    checkValuesSimple(startup);
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
