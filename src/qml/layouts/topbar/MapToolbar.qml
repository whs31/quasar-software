import QtQuick 2.15

import "map" as MapLayouts

Item {
    MapLayouts.MapToolsLayout { id: layout_MapTools;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: 225;
    }

    MapLayouts.MapModeLayout { id: layout_MapMode;
        anchors.right: parent.right;
        anchors.rightMargin: 500;
    }
}
