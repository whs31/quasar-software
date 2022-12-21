import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import DiskManager 1.0

Rectangle 
{
    property int containerHeight: 95;
    
    RoundButton
    {
        id: expandButton;
        icon.source: "qrc:/ui-resources/white/images.png";
        icon.color: "#dae1e5";
        Material.background: "#204040"
        icon.width: 12;
        icon.height: 24;
        height: 32;
        radius: 32;
        opacity: 1;
        text: "Параметры изображений";
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
        opacity: 0.75;
        z: 99;

        //collapsible panel
        property bool shown: false;
        visible: height > 0;
        height: shown ? containerHeight : 0;
        Behavior on height {
            NumberAnimation {
                easing.type: Easing.InOutQuad;
            }
        }
        clip: true

        RoundButton
        {
            id: fetchDirectoryButton;
            icon.source: "qrc:/ui-resources/white/refresh.png";
            icon.color: "#dae1e5";
            Material.background: "#204040"
            icon.width: 12;
            icon.height: 24;
            height: 32;
            radius: 32;
            opacity: 1;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 10;
            text: "Обновить каталог";
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
            onClicked: DiskManager.fetchDirectory();
            z: 99;
        }
        RoundButton
        {
            id: clearDirectoryButton;
            icon.source: "qrc:/ui-resources/white/trashbin.png";
            icon.color: "#dae1e5";
            Material.background: "#b16573"
            icon.width: 12;
            icon.height: 24;
            height: 32;
            radius: 32;
            opacity: 1;
            anchors.left: parent.left;
            anchors.top: fetchDirectoryButton.bottom;
            text: "Очистить кэш";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 11;
            onClicked: DiskManager.clearCache();
            z: 99;
        }
    }
}