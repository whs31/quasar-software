import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import Theme 1.0

Rectangle
{
    property int fixed_width: 100 * Theme.scalingFactor.x;
    property int fixed_height: 25 * Theme.scalingFactor.x;
    property color fill_color: "#de3857";
    property color highlight_color: "#FF0000";
    property int frame_radius: 0 * Theme.scalingFactor.x;
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
        handle: Rectangle {
            color: slider.pressed ? highlight_color : fill_color;
            border.color: fill_color;
            border.width: 1;
            implicitWidth: 4;
            implicitHeight: fixed_height;
            x: slider.visualPosition * (fixed_width - width)
            y: slider.topPadding + slider.availableHeight / 2 - height / 2
            radius: frame_radius;
        }
        background: Rectangle {
            y: slider.topPadding + slider.availableHeight / 2 - height / 2;
            implicitWidth: fixed_width;
            implicitHeight: fixed_height;
            width: fixed_width;
            height: implicitHeight;
            color: "transparent";
            Rectangle {
                width: slider.visualPosition * parent.width;
                height: parent.height;
                color: fill_color;
                radius: frame_radius;
            }
        }
    }
    Component.onCompleted: {
        slider.moved.connect(moved);
    }
}
