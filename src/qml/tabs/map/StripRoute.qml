import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

import Network 1.0
import Route 1.0
import Theme 1.0

MapItemView
{
    property real lat_reevaluate: Network.telemetry.latitude
    onLat_reevaluateChanged: {
        if(Network.recording)
            eventModel.appendNewValue(QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude))
    }

    model: TrackEventModel{ id: eventModel }
    delegate: MapItemGroup {
        MapPolyline {
            path: model.eventPath
            line.width: 5
            line.color: ColorTheme.active.color(ColorTheme.Red)
        }
    }

    Connections {
        target: Network
        function onRecordingChanged() {
            if(Network.recording)
                eventModel.createNewEvent();
        }
    }
}
