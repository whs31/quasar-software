import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import Telemetry 1.0

Map {
    center: QtPositioning.coordinate(Telemetry.latitude, Telemetry.longitude);
    opacity: 0.75;
    zoomLevel: 15;
    tilt: 45;
    activeMapType: supportedMapTypes[1];
    copyrightsVisible: false;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Telemetry.getOsmConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Telemetry.getOsmConfig());
    }
}
