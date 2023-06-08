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
    property string s_MarkerIcon: "qrc:/map/markers/default.png";
    property string s_MarkerColor: "#B0BEC5";

    width: b_Shown ? implicitWidth : 0;
    height: b_Shown ? implicitHeight : 0;
    visible: height > 0;
    enabled: visible;
    Behavior on height { NumberAnimation { duration: 150; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 150; easing.type: Easing.InOutQuad; } }
    clip: true;
    Material.background: Theme.color("dark0");

        ColumnLayout {
            Text {
                font.family: root.mainfont;
                text: "Добавление маркера";
                color: Theme.color("light1");
                font.weight: Font.Bold;
                font.pixelSize: 15;
                horizontalAlignment: Text.AlignHCenter;
            }

            GridLayout {
                columns: 2;

                Text {
                    Layout.fillWidth: true;
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

                Text {
                    Layout.fillWidth: true;
                    text: "Широта:";
                    font.family: root.mainfont;
                    color: Theme.color("light1");
                    font.pixelSize: 14;
                    height: input_MarkerName.height;
                    verticalAlignment: Text.AlignVCenter;
                }

                TextField { id: input_Latitude;
                    property bool b_Valid: /^[0-9.]*$/.test(text);

                    font.family: root.mainfont;
                    font.weight: Font.Bold;
                    font.pixelSize: 14;
                    text: Number(coord_MarkerCoords.latitude).toFixed(8);
                    color: b_Valid ? Theme.color("light1") : Theme.color("red");
                    horizontalAlignment: Text.AlignRight;

                    onEditingFinished: coord_MarkerCoords.latitude = parseFloat(text);
                }

                Text {
                    Layout.fillWidth: true;
                    text: "Долгота:";
                    font.family: root.mainfont;
                    color: Theme.color("light1");
                    font.pixelSize: 14;
                    height: input_MarkerName.height;
                    verticalAlignment: Text.AlignVCenter;
                }

                TextField { id: input_Longitude;
                    property bool b_Valid: /^[0-9.]*$/.test(text);

                    font.family: root.mainfont;
                    font.weight: Font.Bold;
                    font.pixelSize: 14;
                    text: Number(coord_MarkerCoords.longitude).toFixed(8);
                    color: b_Valid ? Theme.color("light1") : Theme.color("red");
                    horizontalAlignment: Text.AlignRight;

                    onEditingFinished: coord_MarkerCoords.longitude = parseFloat(text);
                }
            }

            Row {
                Layout.fillWidth: true;

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#F06292";
                    onPressed: s_MarkerColor = "#F06292";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#FF8A65";
                    onPressed: s_MarkerColor = "#FF8A65";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#FFF176";
                    onPressed: s_MarkerColor = "#FFF176";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#81C784";
                    onPressed: s_MarkerColor = "#81C784";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#80CBC4";
                    onPressed: s_MarkerColor = "#80CBC4";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#90CAF9";
                    onPressed: s_MarkerColor = "#90CAF9";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#BCAAA4";
                    onPressed: s_MarkerColor = "#BCAAA4";
                }

                RoundButton {
                    width: 30;
                    height: 30;
                    Material.background: "#B0BEC5";
                    onPressed: s_MarkerColor = "#B0BEC5";
                }
            }

            Row {
                Layout.alignment: Qt.AlignHCenter;
                Layout.fillWidth: true;
                RoundButton { id: button_OK;
                    width: parent.width / 2;
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
                    width: parent.width / 2;
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
