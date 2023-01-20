import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0
import UX 1.0

Rectangle
{
    property int containerHeight: 130;

    property string textLatitude: "00.0000000";
    property string textLongitude: "00.0000000";
    property string textSpeed: "000.0";
    property string textElevation: "0000";
    property string textSatellites: "--";

    RoundButton
    {
        id: expandButton;
        icon.source: "qrc:/ui-resources/white/link.png";
        icon.color: UX.textWhite;
        Material.background: UX.primaryLight;
        icon.width: 12;
        icon.height: 24;
        width: 225;
        height: 36;
        radius: 16;
        opacity: 1;
        text: "Сетевое подключение";
        font.capitalization: Font.MixedCase;
        font.pixelSize: 13;
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
        opacity: 0.75;
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
            iconsource: "qrc:/ui-resources/white/url.png";
            iconsize: 13;
            primarycolor: UX.primaryLight;
            width: 192;
            height: 20;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 15;
            labeltext: "Подключиться";
            onClicked: ioHandler.reconnect();
            boldness: true;
            z: 99;
        }
        UI.CustomButton
        {
            id: disconnectButton;
            iconsource: "qrc:/ui-resources/white/unlink.png";
            iconsize: 17;
            primarycolor: UX.errorDark;
            accentcolor: UX.errorDarker;
            width: 192;
            height: 20;
            anchors.left: parent.left;
            anchors.top: reconnectButton.bottom;
            anchors.topMargin: 10;
            labeltext: "Отключиться";
            onClicked: ioHandler.disconnect();
            z: 99;
        }
    }
}

