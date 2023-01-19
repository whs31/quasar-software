/*  EXAMPLE USAGE

    UI.ClassicButton
    {
        id: closeButton;
        display_mode: ClassicButton.Mode.IconOnly;
        anchors.top: parent.top;            anchors.topMargin: 6;
        anchors.right: parent.right;        anchors.rightMargin: 6;
        fixed_width: 47;            fixed_height: 27;
        icon_px_size: 15;           icon_source: "qrc:/ui-resources/white/close.png";
        label_text: "Sample text";  label_color: "#de3857";     label_text_size: 12;        label_text_bold: false;
        background_color: "#B16573";
        background_secondary_color: "#701828"; 
        background_radius: 2;
        onClicked: console.log("yay!");
    }

*/

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Rectangle {
    enum Mode {
        IconAndLabel = 1,
        IconOnly = 2,
        LabelOnly = 3
    }

    property int display_mode: ClassicButton.Mode.IconAndLabel;
    property int fixed_width: 100;
    property int fixed_height: 25;

    property int icon_px_size: 16;
    property string icon_source: "qrc:/ui-resources/white/close.png";

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12;
    property bool label_text_bold: false;

    property color background_color: "#701828";
    property color background_secondary_color: "#7D5233"; 
    property int background_radius: 8;

    signal clicked();

    id: control;
    color: background_color;
    radius: background_radius;
    width: fixed_width;
    height: fixed_height;

    ColorAnimation {
            id: animation_hoverOn;
            target: control;
            property: "color";
            to: background_secondary_color;
            duration: 100;
        }
    ColorAnimation {
        id: animation_hoverOff;
        target: control;
        property: "color";
        to: background_color;
        duration: 100;
    }
    SequentialAnimation {
        id: animation_clickColorChange;
        ColorAnimation {
            target: control;
            property: "color";
            to: Qt.darker(background_color, 1.5);
            duration: 100;
        }
        ColorAnimation {
            target: control;
            property: "color";
            to: background_color;
            duration: 100;
        }
    }
    SequentialAnimation {
        id: animation_click;
        PropertyAnimation {
            target: control
            property: "scale"
            to: 0.9
            duration: 50;
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation {
            target: control
            property: "scale"
            to: 1.0
            duration: 50;
            easing.type: Easing.InOutQuad
        }
    }
    Item
    {
        id: m_container;
        width: childrenRect.width;
        anchors.centerIn: parent;
        Image {
            id: ico;
            width: display_mode !== 3 ? icon_px_size : 0;
            height: display_mode !== 3 ? icon_px_size : 0;
            source: icon_source;
            smooth: true;
            antialiasing: true;
            
            anchors.verticalCenter: parent.verticalCenter;
            
        }
        Text {
            text: display_mode !== 2 ? label_text : "";
            font.capitalization: Font.MixedCase;
            font.pixelSize: label_text_size;
            font.bold: label_text_bold;
            color: label_color;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter;
            anchors.left: ico.right;
            anchors.leftMargin: 3;
            anchors.verticalCenter: parent.verticalCenter;
        }
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { animation_hoverOn.start(); }
        onExited: { animation_hoverOff.start(); }
        onClicked: { animation_click.start(); animation_clickColorChange.start(); }
    }
    Component.onCompleted: {
        controlMouseArea.clicked.connect(clicked);
    }
}
