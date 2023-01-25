import QtQuick 2.12
import UX 1.0
import ScaleGridBackend 1.0

Item {
    id: grid;
    width: childrenRect.width;
    height: childrenRect.height;

    ScaleGridBackend
    {
        id: backend;
    }

    ScaleGridTile
    {
        id: testTile;
        cell_size: backend.cellSize;
        color_highlight: UX.textFaded;
        color_main: Qt.darker(UX.textFaded, 1.2);
    }

}
