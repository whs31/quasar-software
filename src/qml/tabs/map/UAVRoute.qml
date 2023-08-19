import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

import QuaSAR.API 1.0

import Route 1.0

MapPolyline {
    function clear() { impl.clear(); }

    enum RouteType
    {
        Full,
        Recent
    }

    property int type: UAVRoute.Recent;


    property var currentPosition: NetworkAPI.telemetry.position
    property real currentSpeed: NetworkAPI.telemetry.velocity.x;
    property int currentSats: NetworkAPI.telemetry.satellites;

    onCurrentPositionChanged: impl.append(currentPosition, currentSpeed, currentSats)

    line.width: 5;
    line.color: theme.yellow
    path: type === UAVRoute.Full ? impl.fullRoute : impl.recentRoute;

    Route { id: impl; }
}
