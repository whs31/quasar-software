import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Telemetry 1.0
import "layouts" as Layouts

Window { id: root;
    width: 1200;
    height: 600;
    visible: true;
    color: "#202329";

    Component.onCompleted: {
        show();
    }

    FontLoader { id: font_Main; source: "qrc:/Overpass.ttf"; }
    property string s_FontMain: font_Main.name;

    property int pitch: 0;
    property int roll: 0;
    property int yaw: 0;
    function updateAxes() {
        if(!lyo_3D.focus)
            lyo_3D.forceActiveFocus();
        if(pitch === -1)
            Telemetry.pitch -= 1;
        if(pitch === 1)
            Telemetry.pitch += 1;
        if(roll === -1)
            Telemetry.roll -= 1;
        if(roll === 1)
            Telemetry.roll += 1;
        if(yaw === -1)
            Telemetry.course -= 1;
        if(yaw === 1)
            Telemetry.course += 1;
    }

    Timer { interval: 20; repeat: true; running: true; onTriggered: updateAxes(); }

//    Layouts.PlaneView {  id: lyo_3D;
//        anchors.left: parent.left;
//        anchors.right: parent.horizontalCenter;
//        anchors.top: parent.top;
//        anchors.bottom: parent.bottom;
//    }

    Layouts.MapView { id: lyo_Map;
        anchors.right: parent.right;
        anchors.left: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 30;
    }

    Layouts.TelemetryLayout { id: lyo_Telemetry;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.margins: 6;
        width: 300;
        height: 230;
    }
}
