import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Rectangle {
    property int iconsize: 16;
    property int buttonwidth: 100;
    property int buttonheight: 20;
    property string iconsource: "qrc:/ui-resources/white/close.png";

    property string labeltext: "Button text!";
    property color textcolor: "#dae1e5";
    property color primarycolor: "#204040";
    property color accentcolor: "#43a1ca";

    signal clicked();

    id: control;
    width: buttonwidth;
    height: buttonheight;
    color: primarycolor;
    radius: 8;

    PropertyAnimation {
        id: animation_scaleup;
        target: control
        property: "scale"
        to: 1.1
        duration: 50;
        easing.type: Easing.InOutQuad
    }
    PropertyAnimation {
        id: animation_scaledown;
        target: control
        property: "scale"
        to: 1.0
        duration: 50;
        easing.type: Easing.InOutQuad
    }
    SequentialAnimation {
        id: animation_colorfadeinout;
        ColorAnimation {
            target: control;
            property: "color";
            to: accentcolor;
            duration: 100;
        }
        ColorAnimation {
            target: control;
            property: "color";
            to: primarycolor;
            duration: 100;
        }
    }
    Item
    {
        id: m_container;
        width: childrenRect.width;
        height: childrenRect.height;
        anchors.centerIn: parent;
        Image {
            id: ico;
            width: iconsize;
            height: iconsize;
            source: iconsource;
            smooth: true;
            antialiasing: true;
        }
        Text {
            text: labeltext;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 11;
            color: textcolor;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
            anchors.left: ico.right;
            anchors.leftMargin: 3;
        }
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { control.color = Qt.lighter(primarycolor, 1.5); animation_scaleup.start(); }
        onExited: { control.color = primarycolor; animation_scaledown.start(); }
        onClicked: { animation_colorfadeinout.start(); }
        Rectangle {
            anchors.fill: parent;
            color: "#FFFF00"
            visible: false;
        }
    }
    Component.onCompleted: {
        controlMouseArea.clicked.connect(clicked);
    }

}