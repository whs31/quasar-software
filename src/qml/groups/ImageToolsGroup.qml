import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import DiskManager 1.0
import ImageManager 1.0

Rectangle 
{
    property int containerHeight: 130;
    
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
        text: "Работа с изображениями";
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

        UI.CustomButton
        {
            id: fetchDirectoryButton;
            iconsource: "qrc:/ui-resources/white/refresh.png";
            iconsize: 11;
            primarycolor: "#204040";
            width: 145;
            height: 16;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 10;
            labeltext: "Обновить каталог";
            onClicked: DiskManager.fetchDirectory();
            z: 99;
        }
        UI.CustomButton
        {
            id: changeDirectoryButton;
            iconsource: "qrc:/ui-resources/white/folder.png";
            iconsize: 11;
            primarycolor: "#204040";
            width: 145;
            height: 16;
            anchors.left: parent.left;
            anchors.top: fetchDirectoryButton.bottom;
            anchors.topMargin: 10;
            labeltext: "Изменить каталог";
            onClicked: ioHandler.changeDirectory();
            z: 99;
        }
        UI.CustomButton
        {
            id: clearMapButton;
            iconsource: "qrc:/ui-resources/white/map.png";
            iconsize: 11;
            primarycolor: "#b16573";
            accentcolor: "#701828";
            width: 145;
            height: 16;
            anchors.left: parent.left;
            anchors.top: changeDirectoryButton.bottom;
            anchors.topMargin: 10;
            labeltext: "Очистить карту";
            onClicked: 
            {
                imageModel.clear();
                imageUIModel.clear();
                ImageManager.clearAll();
            }
            z: 99;
        }
        UI.CustomButton
        {
            id: clearDirectoryButton;
            iconsource: "qrc:/ui-resources/white/trashbin.png";
            iconsize: 11;
            primarycolor: "#b16573";
            accentcolor: "#701828";
            width: 145;
            height: 16;
            anchors.left: parent.left;
            anchors.top: clearMapButton.bottom;
            anchors.topMargin: 10;
            labeltext: "Очистить кэш";
            onClicked: DiskManager.clearCache();
            z: 99;
        }
    }
}