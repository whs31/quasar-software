import QtQuick 2.15
import QtQuick.Controls 2.12
import Theme 1.0

Rectangle {
    property alias container : loader.sourceComponent

    property int fixed_width: 100 * Theme.scalingFactor.x;
    property int fixed_height: 25 * Theme.scalingFactor.y;
    property int fixed_drop: 200 * Theme.scalingFactor.y;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12 * Theme.scalingFactor.y;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int label_textAlignment: Text.AlignHCenter;

    property color highlight_color: "#7D5233";
    property int frame_radius: 8 * Theme.scalingFactor.x;
    property int frame_width: 1;
    property bool frame_filled: false;
    property color frame_fill_color: "#FFFF00";

    property bool shown: false;

    id: control;
    color: frame_filled ? frame_fill_color : "transparent";
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
        to: frame_filled ? frame_fill_color : "transparent";
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
            to: frame_filled ? frame_fill_color : "transparent";
            duration: 70;
        }
    }
    Rectangle
    {
        id: dropSection;
        width: fixed_width;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.bottom; anchors.topMargin: -frame_radius;
        color: label_color;
        border.width: frame_width;
        radius: frame_radius;
        border.color: label_color;

        //collapsible panel
        visible: height > 0;
        height: shown ? fixed_drop : 0;
        Behavior on height {
            NumberAnimation {
                duration: 100;
                easing.type: Easing.InOutQuad;
            }
        }
        //clip: true;
        z: 90;

        Loader { id: loader; opacity: shown ? 1 : 0; Behavior on opacity {
                NumberAnimation {
                    duration: 200;
                    easing.type: Easing.InOutQuad;
                }
            } }
    }
    Item
    {
        id: dropButton;
        width: childrenRect.width;
        anchors.fill: parent;
        Image {
            id: ico;
            width: 11 * Theme.scalingFactor.x;
            height: 11 * Theme.scalingFactor.y;
            source: "qrc:/icons/down.png";
            smooth: true;
            antialiasing: true;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4 * Theme.scalingFactor.x;
            z: 91;
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
            anchors.fill: parent;
            anchors.leftMargin: 5 * Theme.scalingFactor.x;
            anchors.rightMargin: 5 * Theme.scalingFactor.x;
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
