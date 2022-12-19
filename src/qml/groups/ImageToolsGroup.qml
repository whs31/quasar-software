import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI

UI.RoundPane {
    id: base;
    radius: 10;
    Material.elevation: 20;

    RowLayout {
        spacing: -20;
        anchors.fill: parent;
        anchors.topMargin: -20;
        anchors.leftMargin: -8;
        anchors.bottomMargin: -40;
        anchors.rightMargin: -20;
        RoundButton
        {
            id: fetchDirectory;
            icon.source: "qrc:/ui-resources/white/refresh.png";
            icon.color: "#dae1e5";
            radius: 10;
            opacity: 1;
            text: "Обновить каталог с РЛИ";
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
            Layout.preferredHeight: 30;
            onClicked: {
                //1
            }
            z: 100;
        }
        RoundButton
        {
            id: clearDirectory;
            icon.source: "qrc:/ui-resources/white/trashbin.png";
            icon.color: "#dae1e5";
            Material.background: "#b16573"
            radius: 10;
            opacity: 1;
            text: "Очистить кэш";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 11;
            Layout.preferredHeight: 30;
            onClicked: {
                //2
            }
            z: 100;
        }
    }
}
