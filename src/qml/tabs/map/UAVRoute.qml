import QtQuick 2.15
import Network 1.0
import QtLocation 5.15
import QtPositioning 5.15
import Route 1.0
import Theme 1.0

MapPolyline {
    function clear() { c_Route.clear(); }

    enum RouteType
    {
        Full,
        Recent
    }

    property int type: UAVRoute.Recent;


    property real fl_CurrentLat: Network.telemetry.latitude;
    property real fl_CurrentSpeed: Network.telemetry.velocityCourse;
    property int i_CurrentSats: Network.telemetry.satellites;

    onFl_CurrentLatChanged: c_Route.append(QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude),
                                           fl_CurrentSpeed, i_CurrentSats);

    line.width: 5;
    line.color: Theme.color("yellow");
    path: type === UAVRoute.Full ? c_Route.fullRoute : c_Route.recentRoute;

    Route { id: c_Route; }
}
