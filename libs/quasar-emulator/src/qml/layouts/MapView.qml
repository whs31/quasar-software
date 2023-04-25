import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import Telemetry 1.0

Map {
    center: QtPositioning.coordinate(Telemetry.latitude, Telemetry.longitude);
    opacity: 0.5;
    zoomLevel: 15;
    plugin: Plugin { name: "osm"; }
}
