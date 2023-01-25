import QtQuick 2.12

Item {
    property color color_highlight: "#FFFFFF";
    property color color_main: "#AAAAAA";
    property int cell_size: 128;

    id: tile;
    width: cell_size * 0.94;
    height: cell_size * 0.87;

    Rectangle
    {
        id: lineTop;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.topMargin: tile.height / 4;
        height: 1.5;
        color: color_highlight;
    }
    Rectangle
    {
        id: lineLeft;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.leftMargin: tile.width / 4;
        width: 1.5;
        color: color_highlight;
    }
    Rectangle
    {
        id: lineBottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: tile.height / 4;
        height: 1;
        color: color_main;
    }
    Rectangle
    {
        id: lineRight;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: tile.width / 4;
        width: 1;
        color: color_main;
    }
}
