import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.15

import Theme 1.0
import ClickHandler 1.0
import Markers 1.0

Pane {
    function open(latitude, longitude) {
        coord_MarkerCoords = QtPositioning.coordinate(latitude, longitude);
        s_MarkerName = "МАРКЕР №" + Number(MarkersModel.rowCount() + 1);
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
    property string s_MarkerIcon: "qrc:/map/markers/flag.png";
    property string s_MarkerColor: Theme.color("color2");

    width: b_Shown ? implicitWidth : 0;
    height: b_Shown ? implicitHeight : 0;
    visible: height > 0;
    enabled: visible;
    Behavior on height { NumberAnimation { duration: 150; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 150; easing.type: Easing.InOutQuad; } }
    clip: true;
    Material.background: Theme.color("dark0");

    Column {
        Text {
            font.family: root.mainfont;
            text: "Добавление маркера";
            color: Theme.color("light1");
            font.weight: Font.Bold;
            font.pixelSize: 15;
            horizontalAlignment: Text.AlignHCenter;
        }

        ColumnLayout {
            Row {
                Layout.fillWidth: true;

                Text {
                    text: "Имя маркера:     ";
                    font.family: root.mainfont;
                    color: Theme.color("light1");
                    font.pixelSize: 14;
                    height: input_MarkerName.height;
                    verticalAlignment: Text.AlignVCenter;
                }

                TextField { id: input_MarkerName;
                    font.family: root.mainfont;
                    font.weight: Font.Bold;
                    font.pixelSize: 14;
                    text: s_MarkerName;
                    color: Theme.color("light1");
                    horizontalAlignment: Text.AlignRight;

                    onEditingFinished: s_MarkerName = text;
                }
            }
        }

        Row {
            RoundButton { id: button_OK;
                width: 100;
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
                width: 100;
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
}
