import QtQuick 2.12

Item {
    id: grid;
    width: childrenRect.width;
    height: childrenRect.height;
    ScaleGridTile
    {
        id: testTile;
        cell_size: 128;

    }
}
