import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

import QuaSAR.API 1.0
import Route 1.0
import Theme 1.0

MapItemView
{
    property real lat_reevaluate: NetworkAPI.telemetry.position.latitude
    onLat_reevaluateChanged: {
        if(NetworkAPI.remote.isRecordingStrip)
            eventModel.appendNewValue(NetworkAPI.telemetry.position)
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
        target: NetworkAPI.remote
        function onRecordingStripChanged() {
            if(NetworkAPI.remote.isRecordingStrip)
                eventModel.createNewEvent();
        }
    }
}
