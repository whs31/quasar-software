import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Rectangle
{
    property int containerHeight: 110;

    property string textLatitude: "00.0000000";
    property string textLongitude: "00.0000000";
    property string textSpeed: "000.0";
    property string textElevation: "0000";
    property string textSatellites: "--";

    RoundButton
    {
        id: expandButton;
        icon.source: "qrc:/ui-resources/white/link.png";
        icon.color: "#dae1e5";
        Material.background: "#204040"
        icon.width: 12;
        icon.height: 24;
        height: 32;
        radius: 32;
        opacity: 1;
        text: "Удаленное соединение с РЛС";
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
        UI.CustomButton
        {
            id: reconnectButton;
            iconsource: "qrc:/ui-resources/white/refresh.png";
            iconsize: 11;
            primarycolor: "#204040";
            width: 175;
            height: 16;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 10;
            labeltext: "Повторное подключение";
            onClicked: ioHandler.reconnect();
            z: 99;
        }
        UI.CustomButton
        {
            id: disconnectButton;
            iconsource: "qrc:/ui-resources/white/close.png";
            iconsize: 11;
            primarycolor: "#b16573";
            accentcolor: "#701828";
            width: 175;
            height: 16;
            anchors.left: parent.left;
            anchors.top: reconnectButton.bottom;
            anchors.topMargin: 5;
            labeltext: "Отключиться";
            onClicked: ioHandler.disconnect();
            z: 99;
        }
    }
}

