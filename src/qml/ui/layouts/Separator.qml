import QtQuick 2.15

Rectangle {
    property int fixed_height: 20;
    property real fixed_width: 1.5;
    property color line_color: "#FF0000";

    color: line_color;
    width: fixed_width;
    height: fixed_height;
}
