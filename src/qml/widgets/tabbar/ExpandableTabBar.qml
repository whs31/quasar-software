import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

import Theme 1.0

TabBar {
    id: root;
    spacing: 10;
    topPadding: 3;
    bottomPadding: 3;
    leftPadding: 5;
    palette {
        base: Theme.color("dark1");
    }
    contentItem: ListView {
        model: root.contentModel;
        currentIndex: root.currentIndex;
        spacing: root.spacing;
        orientation: Qt.Horizontal;
        boundsBehavior: Flickable.StopAtBounds;
        flickableDirection: Flickable.AutoFlickIfNeeded;
        snapMode: ListView.SnapToItem;
        highlightMoveDuration: 0;
        highlightRangeMode: ListView.ApplyRange;
        preferredHighlightBegin: 0;
        preferredHighlightEnd: width;
        clip: true;
    }
    background: Rectangle {
        color: root.palette.base;

        RectangularGlow {
            z: -1;
            anchors.fill: parent;
            glowRadius: 8;
            color: "#80000000";
            cornerRadius: parent.radius + glowRadius;
            cached: true;
        }
    }
}
