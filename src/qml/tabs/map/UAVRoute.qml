import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

import QuaSAR.API 1.0

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


    property real fl_CurrentLat: NetworkAPI.telemetry.position.latitude
    property real fl_CurrentSpeed: NetworkAPI.telemetry.velocity.x;
    property int i_CurrentSats: NetworkAPI.telemetry.satellites;

    onFl_CurrentLatChanged: c_Route.append(NetworkAPI.telemetry.position,
                                           fl_CurrentSpeed, i_CurrentSats);

    line.width: 5;
    line.color: ColorTheme.active.color(ColorTheme.Yellow)
    path: type === UAVRoute.Full ? c_Route.fullRoute : c_Route.recentRoute;

    Route { id: c_Route; }
}
