import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

Window {
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    width: 700;
    height: 800;

    color: Theme.color("dark0");
    modality: Qt.NonModal;
    title: "Параметры формирования";

    ScrollView { id: view;
        width: parent.width;
        height : parent.height;
        contentWidth: column.width;
        contentHeight: column.height;
        clip : true;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.topMargin: 20;
        anchors.bottom: buttonGroup.top;
        anchors.bottomMargin: 5;
    }

    Row { id: buttonGroup;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_OK;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            text: "OK";
            onPressed: hide();
        }
    }
}
