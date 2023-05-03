import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import Paths 1.0
import RulerModel 1.0

import "map" as MapTab;

Map { id: c_Map;
    property int i_MapMode: 1; // { 0 - offline, 5 - schema, 4 - hybrid, 1 - sattelite }

    layer.enabled: true;
    layer.samples: 8;
    layer.smooth: true;

    tilt: 15;
    gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.PinchGesture;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Paths.mapConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Paths.mapConfig());
    }

    activeMapType: c_Map.supportedMapTypes[i_MapMode];
    center: QtPositioning.coordinate(60, 30);
    zoomLevel: 5;
    copyrightsVisible: false;
    z: 0;

    MouseArea { id: c_MapMouseArea;
        hoverEnabled: true;
        anchors.fill: parent;

        onClicked: {
            c_RulerModel.insertPoint(c_Map.toCoordinate(Qt.point(mouseX, mouseY)), 0);
        }
    }


    MapTab.UAV { }
    MapTab.UAVRoute { }

    RulerModel { id: c_RulerModel; }
    MapTab.RulerItem { id: c_Ruler; fl_LastLatitude: c_RulerModel.lastLatitude; fl_LastLongitude: c_RulerModel.lastLongitude; }
}
