import QtQuick 2.15
import Network 1.0
import QtLocation 5.15
import QtPositioning 5.15
import Route 1.0
import Theme 1.0

MapPolyline {
    property var qgeo_CurrentCoord: QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude);
    property real fl_CurrentSpeed: Network.telemetry.velocityCourse;
    property int i_CurrentSats: -1;

        // on changed
    line.width: 5;
    line.color: Theme.color("yellow");
    path: c_Route.fullRoute;

    Route { id: c_Route; }
}
