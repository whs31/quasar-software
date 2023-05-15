import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtPositioning 5.15

import Theme 1.0
import ClickHandler 1.0
import Markers 1.0

Pane {
    function open(latitude, longitude) {
        coord_MarkerCoords = QtPositioning.coordinate(latitude, longitude);
        b_Shown = true;
    }

    function accept()
    {
        ClickHandler.addMarker(coord_MarkerCoords.latitude, coord_MarkerCoords.longitude, s_MarkerName, s_MarkerColor, s_MarkerIcon);
        b_Shown = false;
    }

    property bool b_Shown: false;
    property var coord_MarkerCoords: QtPositioning.coordinate(0, 0);
    property string s_MarkerName: "МАРКЕР №" + MarkersModel.rowCount();
    property string s_MarkerIcon: "qrc:/map/markers/default.png";
    property string s_MarkerColor: Theme.color("orange");

    width: b_Shown ? implicitWidth : 0;
    height: b_Shown ? implicitHeight : 0;
    visible: height > 0;
    enabled: visible;
    Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    clip: true;
    Material.background: Theme.color("dark0");

    implicitWidth: 300;
    implicitHeight: 400;

    Row {
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_OK;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark0");
            text: "ОК";
            onPressed: accept();
        }

        RoundButton { id: button_Cancel;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark0");
            text: "Отмена";
            onPressed: b_Shown = false;
        }
    }
}
