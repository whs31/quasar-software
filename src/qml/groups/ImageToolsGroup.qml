import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import DiskManager 1.0

Rectangle 
{
    RoundButton
    {
        id: fetchDirectoryButton;
        icon.source: "qrc:/ui-resources/white/refresh.png";
        icon.color: "#dae1e5";
        icon.width: 12;
        icon.height: 24;
        height: 32;
        radius: 32;
        opacity: 1;
        anchors.left: parent.left;
        anchors.top: parent.top;
        text: "Обновить каталог с РЛИ";
        font.capitalization: Font.MixedCase; 
        font.pixelSize: 11;
        onClicked: DiskManager.fetchDirectory();
        z: 100;
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
        anchors.left: fetchDirectoryButton.right;
        anchors.top: fetchDirectoryButton.top;
        text: "Очистить кэш";
        font.capitalization: Font.MixedCase;
        font.pixelSize: 11;
        onClicked: DiskManager.clearCache();
        z: 100;
    }
}