import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0

Rectangle {
    property int iconsize: 16;
    property string iconsource: "qrc:/ui-resources/white/close.png";

    property string labeltext: "Button text!";
    property color textcolor: UX.textWhite;
    property color primarycolor: UX.primaryLight;
    property color accentcolor: UX.infoLighter; 
    property bool boldness: false;

    signal clicked();

    id: control;
    color: primarycolor;
    radius: 8;

    PropertyAnimation {
        id: animation_scaleup;
        target: control
        property: "scale"
        to: 1.05
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
        //height: childrenRect.height;
        anchors.centerIn: parent;
        Image {
            id: ico;
            width: iconsize;
            height: iconsize;
            source: iconsource;
            smooth: true;
            antialiasing: true;
            
            anchors.verticalCenter: parent.verticalCenter;
            
        }
        Text {
            text: labeltext;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 13;
            font.bold: boldness;
            color: textcolor;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
            anchors.left: ico.right;
            anchors.leftMargin: 3;
            anchors.verticalCenter: parent.verticalCenter;
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
            color: "#FFFF00";
            visible: false;
        }
    }
    Component.onCompleted: {
        controlMouseArea.clicked.connect(clicked);
    }

}
