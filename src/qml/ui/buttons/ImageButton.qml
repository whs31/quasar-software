import QtQuick 2.12
import QtQuick.Controls 2.12
import DynamicResolution 1.0

Rectangle {
    property int fixed_width: 100 * DynamicResolution.kw;
    property int fixed_height: 25 * DynamicResolution.kh;
    property string image_source: "qrc:/ui-resources/white/close.png";
    property color frame_color: "#701828";
    property color hover_color: "#7D5233";
    property int frame_width: 1;
    property int frame_radius: 2 * DynamicResolution.kw;

    signal clicked();

    id: control;
    color: "transparent";
    radius: frame_radius;
    border.width: frame_width;
    border.color: frame_color;
    width: fixed_width;
    height: fixed_height;

    ColorAnimation {
        id: animation_hoverOn;
        target: control;
        property: "color";
        to: hover_color;
        duration: 100;
    }
    ColorAnimation {
        id: animation_hoverOff;
        target: control;
        property: "color";
        to: "transparent";
        duration: 100;
    }
    SequentialAnimation {
        id: animation_clickColorChange;
        ColorAnimation {
            target: control;
            property: "color";
            to: Qt.darker(hover_color, 1.5);
            duration: 100;
        }
        ColorAnimation {
            target: control;
            property: "color";
            to: "transparent";
            duration: 100;
        }
    }
    SequentialAnimation {
        id: animation_click;
        PropertyAnimation {
            target: control;
            property: "scale";
            to: 0.9;
            duration: 50;
            easing.type: Easing.InOutQuad;
        }
        PropertyAnimation {
            target: control;
            property: "scale";
            to: 1.0;
            duration: 50;
            easing.type: Easing.InOutQuad;
        }
    }
    Image {
        id: imageFiller;
        anchors.fill: parent;
        source: image_source;
        smooth: true;
        antialiasing: true;
        opacity: 0.8;
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { animation_hoverOn.start(); }
        onExited: { animation_hoverOff.start(); }
        onClicked: { animation_click.start(); animation_clickColorChange.start(); forceActiveFocus(); }
    }
    Component.onCompleted: {
        controlMouseArea.clicked.connect(clicked);
    }
}
