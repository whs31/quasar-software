import QtQuick 2.12
import QtQuick.Controls 2.12
import DynamicResolution 1.0

Rectangle {
    property int fixed_width: 100 * DynamicResolution.kw;
    property int fixed_height: 25 * DynamicResolution.kh;

    property int icon_px_size: 16 * DynamicResolution.kh;
    property string icon_source: "qrc:/ui-resources/white/close.png";
    property string tooltip_text: "Sample text";
    property bool tooltip_enabled: false;
    property string label_text_family: "helvetica";

    property color highlight_color: "#7D5233";
    property color frame_color: "#FF0000";
    property bool frame_enabled: true;
    property int frame_radius: 8 * DynamicResolution.kw;
    property int frame_width: 1;

    signal clicked();

    id: control;
    color: "transparent";
    radius: frame_radius;
    border.width: frame_width;
    border.color: frame_enabled ? frame_color : "transparent";
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
    Image {
        id: ico;
        width: icon_px_size;
        height: icon_px_size;
        source: icon_source;
        smooth: true;
        antialiasing: true;
        anchors.centerIn: parent;
    }
    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { animation_hoverOn.start(); }
        onExited: { animation_hoverOff.start(); }
        onClicked: { animation_click.start(); animation_clickColorChange.start(); forceActiveFocus(); }
    }
    ToolTip {
        id: m_tooltip;
        delay: 750;
        timeout: 5000;
        visible: tooltip_enabled ? controlMouseArea.containsMouse : false;
        font.capitalization: Font.AllUppercase;
        font.pixelSize: 10;
        contentItem: Text {
            text: tooltip_text;
            font: label_text_family;
            color: "#121617";
        }
        background: Rectangle {
            color: "#dae1e5";
            radius: 10;
            opacity: 0.75;
        }
    }
    Component.onCompleted: {
        controlMouseArea.clicked.connect(clicked);
    }
}
