import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0

Window {
    function open(header, content, icon) {
        title = header;
        contentText.text = content;

        if(icon === "info")
            iconItem.source = "qrc:/icons/dialog/info.png";
        else if(icon === "warn")
            iconItem.source = "qrc:/icons/dialog/warning.png";
        else
            iconItem.source = "qrc:/icons/dialog/error.png";

        show();
    }

    function close() { hide(); }

    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark0");

    width: 500;
    height: 170;

    color: Theme.color("dark0");
    modality: Qt.ApplicationModal;
    title: "-";

    Image { id: iconItem;
        width: 75;
        height: 75;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: 15;
        source: "qrc:/icons/dialog/info.png";
        mipmap: true;
    }

    Text { id: contentText;
        anchors.right: parent.right;
        anchors.rightMargin: 15;
        anchors.left: iconItem.right;
        anchors.leftMargin: 15;
        anchors.verticalCenter: parent.verticalCenter;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignTop;
        font.family: root.mainfont;
        color: Theme.color("light1");
        font.bold: true;
        font.pixelSize: 14;
        wrapMode: Text.WordWrap;
    }

    RoundButton { id: button_Close;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        width: 200;
        font.family: root.mainfont;
        font.weight: Font.Bold;
        height: 44;
        radius: 4;
        Material.elevation: 30;
        Material.background: Theme.color("dark0");
        text: "Ок";
        onPressed: close();
    }
}
