import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Map { id: c_Map;
    plugin: Plugin {
        name: "osm";
    }

    center: QtPositioning.coordinate(43.318154, 40.218245);
    zoomLevel: 14;
    activeMapType: c_Map.supportedMapTypes[5];
}
