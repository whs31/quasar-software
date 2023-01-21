import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Rectangle
{
    property int fixed_width: 100;
    property int fixed_height: 25;
    property color fill_color: "#de3857";
    property color highlight_color: "#FF0000";
    property int frame_radius: 0;
    property int frame_width: 1;

    property real slider_fromvalue: 0;
    property real slider_tovalue: 1;
    property bool slider_horizontal: true;
    property alias slider_value: slider.value;

    signal moved();

    id: control;
    color: "transparent";
    radius: frame_radius;
    border.width: frame_width;
    border.color: fill_color;
    width: fixed_width;
    height: fixed_height;

    Slider {
        id: slider;
        anchors.fill: parent;
        live: true;
        snapMode: Slider.NoSnap;
        to: slider_tovalue;
        from: slider_fromvalue;
        wheelEnabled: false;
        clip: false;
        orientation: slider_horizontal ? Qt.Horizontal : Qt.Vertical;
        value: 2;
    }
//    MouseArea {
//        id: controlMouseArea;
//        hoverEnabled: true;
//        anchors.fill: parent;
//        //onEntered: { animation_hoverOn.start(); }
//        //onExited: { animation_hoverOff.start(); }
//        //onClicked: { animation_click.start(); animation_clickColorChange.start(); forceActiveFocus(); }
//    }
    Component.onCompleted: {
        slider.moved.connect(moved);
    }
}
