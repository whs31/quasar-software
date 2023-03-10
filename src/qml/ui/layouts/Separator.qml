import QtQuick 2.15
import Theme 1.0

Rectangle {
    property int fixed_height: 20 * Theme.scalingFactor.y;
    property real fixed_width: 1.5 * Theme.scalingFactor.x;
    property color line_color: "#FF0000";

    color: line_color;
    width: fixed_width;
    height: fixed_height;
}
