import QtQuick 2.15
import DynamicResolution 1.0

Rectangle {
    property int fixed_height: 20 * DynamicResolution.kh;
    property real fixed_width: 1.5 * DynamicResolution.kw;
    property color line_color: "#FF0000";

    color: line_color;
    width: fixed_width;
    height: fixed_height;
}
