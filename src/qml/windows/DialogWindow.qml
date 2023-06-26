import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0

Pane { id: control;
    function open(header, content, icon, uid_num) {
        title = header;
        contentText.text = content;

        if(icon === "info")
            iconItem.source = "qrc:/icons/dialog/info.png";
        else if(icon === "warn")
            iconItem.source = "qrc:/icons/dialog/warning.png";
        else
            iconItem.source = "qrc:/icons/dialog/error.png";

        uid = uid_num;
        b_Shown = true;
    }

    function accept() { b_Shown = false; closed(true, uid); }
    function decline() { b_Shown = false; closed(false, uid); }
    signal closed(bool status, int uid);

    property bool b_Shown: false;
    property string title;
    property int uid: 0;

    width: b_Shown ? implicitWidth : 0;
    height: b_Shown ? implicitHeight : 0;
    visible: height > 0;
    enabled: visible;
    Behavior on height { NumberAnimation { duration: 100; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 100; easing.type: Easing.InOutQuad; } }

    clip: true;

    Material.background: ColorTheme.active.color(ColorTheme.Dark)
    Material.elevation: 200;

    implicitWidth: 600;
    implicitHeight: 180;

    Image { id: iconItem;
        width: 75;
        height: 75;
        anchors.verticalCenterOffset: -10;
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
        anchors.verticalCenterOffset: -10;
        anchors.verticalCenter: parent.verticalCenter;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignTop;
        font.family: root.mainfont;
        color: ColorTheme.active.color(ColorTheme.Text)
        font.bold: true;
        font.pixelSize: 14;
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
    }

    Row {
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_OK;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.Dark)
            text: "Ок";
            onPressed: accept();
        }

        RoundButton { id: button_Cancel;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.Dark)
            text: "Отмена";
            onPressed: decline();
        }
    }
}
