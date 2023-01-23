import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    property int fixed_width: 100;
    property int fixed_height: 25;

    property color background_color: "#7D5233";
    property color highlight_color: "#FF0000";
    property int background_radius: 8;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int label_textAlignment: Text.AlignHCenter;

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
        to: highlight_color;
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
            to: Qt.darker(highlight_color, 1.5);
            duration: 70;
        }
        ColorAnimation {
            target: control;
            property: "color";
            to: background_color;
            duration: 70;
        }
    }
    SequentialAnimation {
        id: animation_click;
        PropertyAnimation {
            target: control;
            property: "scale"
            to: 0.9
            duration: 50;
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation {
            target: control;
            property: "scale"
            to: 1.0
            duration: 50;
            easing.type: Easing.InOutQuad
        }
    }
    Text {
        text: label_text;
        font.capitalization: Font.MixedCase;
        font.pixelSize: label_text_size;
        font.family: label_text_family;
        font.bold: label_text_bold;
        color: label_color;
        opacity: enabled ? 1.0 : 0.3
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: label_textAlignment;
        anchors.fill: parent; anchors.margins: background_radius + 2;
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