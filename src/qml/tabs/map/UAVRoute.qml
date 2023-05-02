import QtQuick 2.15
import Network 1.0
import QtLocation 5.15
import QtPositioning 5.15
import Route 1.0
import Theme 1.0

MapPolyline {
    layer.enabled: true;
    layer.samples: 16;

    property var qgeo_CurrentCoord: QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude);
    property real fl_CurrentSpeed: Network.telemetry.velocityCourse;
    property int i_CurrentSats: -1;

    onQgeo_CurrentCoordChanged: c_Route.append(qgeo_CurrentCoord, fl_CurrentSpeed, i_CurrentSats);

    line.width: 5;
    line.color: Theme.color("yellow");
    path: c_Route.fullRoute;

    Route { id: c_Route; }
}
