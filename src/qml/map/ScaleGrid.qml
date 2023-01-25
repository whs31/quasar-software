import QtQuick 2.12
import UX 1.0

Item {
    id: grid;
    width: childrenRect.width;
    height: childrenRect.height;

    ScaleGridTile
    {
        id: testTile;
        cell_size: 128;
        color_highlight: UX.textFaded;
        color_main: Qt.darker(UX.textFaded, 1.2);
    }
}
