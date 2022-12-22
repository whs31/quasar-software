import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Rectangle 
{
    property int containerHeight: 90;

    property string textLatitude: "00.0000000";
    property string textLongitude: "00.0000000";
    property string textSpeed: "000.0";
    property string textElevation: "0000";
    property string textSatellites: "--";
    
    RoundButton
    {
        id: expandButton;
        icon.source: "qrc:/ui-resources/white/gps.png";
        icon.color: "#dae1e5";
        Material.background: "#204040"
        icon.width: 12;
        icon.height: 24;
        height: 32;
        radius: 32;
        opacity: 1;
        text: "Телеметрия РЛС / Статус";
        font.capitalization: Font.MixedCase; 
        font.pixelSize: 11;
        onClicked: box.shown = !box.shown;
        z: 100;
    }

    UI.RoundPane {
        id: box;
        anchors.top: expandButton.top;
        anchors.topMargin: 10;
        anchors.left: expandButton.left;
        anchors.leftMargin: 5;
        anchors.right: expandButton.right;
        anchors.rightMargin: 5;
        opacity: 0.85;
        z: 99;

        //collapsible panel
        property bool shown: true;
        visible: height > 0;
        height: shown ? containerHeight : 0;
        Behavior on height {
            NumberAnimation {
                easing.type: Easing.InOutQuad;
            }
        }
        clip: true

        Text {
            id: latitudeText;
            anchors.top: parent.top;
            anchors.topMargin: 10;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            color: "#dae1e5";
            textFormat: Text.RichText
            text: "Широта: " + "<font color=\"#b4b4dc\"><b>" + Number(RuntimeData.latitude).toFixed(7) + "°";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: longitudeText;
            color: "#dae1e5";
            anchors.top: latitudeText.bottom;
            anchors.topMargin: 2;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            textFormat: Text.RichText
            text: "Долгота: " + "<font color=\"#b4b4dc\"><b>" + Number(RuntimeData.longitude).toFixed(7) + "</b></font>" + "°";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: speedText;
            anchors.top: longitudeText.bottom;
            anchors.topMargin: 2;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            color: "#dae1e5";
            textFormat: Text.RichText
            text: "Скорость: " + "<font color=\"#c4bb4b\"><b>" + Number(RuntimeData.speed).toFixed(1) + "</b></font>" + " <i>км/ч</i>";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: elevationText;
            anchors.top: speedText.bottom;
            anchors.topMargin: 2;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            color: "#dae1e5";
            textFormat: Text.RichText;
            text: "Высота: " + "<font color=\"#c4bb4b\"><b>" + Number(RuntimeData.elevation).toFixed(0) + "</b></font>" + " <i>м</i>";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }
}

