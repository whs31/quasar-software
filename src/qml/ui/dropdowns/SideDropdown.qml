import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
    property alias container : loader.sourceComponent

    property int fixed_width: 100;
    property int fixed_height: 25;
    property int fixed_drop_height: 200;
    property int fixed_drop_width: 200;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property color drop_color: "#de3857";
    property int label_text_size: 12;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int label_textAlignment: Text.AlignHCenter;
    property bool label_uppercase: true;

    property color highlight_color: "#7D5233";
    property int frame_radius: 8;
    property int frame_width: 1;

    property bool shown: false;

    id: control;
    color: "transparent";
    radius: frame_radius;
    border.width: frame_width;
    border.color: label_color;
    width: fixed_width;
    height: fixed_height;
    z: 91;

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
        to: "transparent";
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
            to: "transparent";
            duration: 70;
        }
    }
    Rectangle
    {
        id: dropSection;
        anchors.left: parent.right;
        anchors.top: parent.top;
        color: drop_color;
        border.width: frame_width;
        radius: frame_radius;
        border.color: label_color;

        //collapsible panel
        visible: height > 0;
        width: shown ? fixed_drop_width : 0;
        height: shown ? fixed_drop_height : 0;
        clip: true;
        Behavior on height {
            NumberAnimation
            {
                duration: 100;
                easing.type: Easing.InOutQuad;
            }
        }
        Behavior on width {
            NumberAnimation {
                duration: 100;
                easing.type: Easing.InOutQuad;
            }
        }

        Loader { id: loader; }
    }
    Item
    {
        id: dropButton;
        width: childrenRect.width;
        anchors.fill: parent;
        Text {
            text: label_text;
            font.pixelSize: label_text_size;
            font.family: label_text_family;
            font.bold: label_text_bold;
            color: label_color;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: label_textAlignment;
            anchors.fill: parent;
            anchors.leftMargin: 5; anchors.rightMargin: 5;
            font.capitalization: label_uppercase ? Font.AllUppercase : Font.MixedCase;
            z: 91;
        }
        z: 91;
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent;
        onEntered: { animation_hoverOn.start(); }
        onExited: { animation_hoverOff.start(); }
        onClicked: { animation_clickColorChange.start(); shown = !shown; }
    }
}
