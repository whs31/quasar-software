import QtQuick 2.12

Item {
    Rectangle {
        id: bottomPan;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        width: 300;
        height: 40;
        color: "#000055";
        opacity: 0;
        MouseArea {
            id: bottomPanHoverArea;
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape: Qt.SizeVerCursor;
            onEntered: { bottomPanning = true; }
            onExited: { bottomPanning = false; }
        }
    }
    Rectangle {
        id: topPan;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        width: 300;
        height: 40;
        color: "#00FF00";
        opacity: 0;
        MouseArea {
            id: topPanHoverArea;
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape: Qt.SizeVerCursor;
            onEntered: { topPanning = true; }
            onExited: { topPanning = false; }
        }
    }
    Rectangle {
        id: leftPan;
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 40;
        height: 220;
        color: "#FF00FF";
        opacity: 0;
        MouseArea {
            id: leftPanHoverArea;
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape: Qt.SizeHorCursor;
            onEntered: { leftPanning = true; }
            onExited: { leftPanning = false; }
        }
    }
    Rectangle {
        id: rightPan;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        width: 40;
        height: 220;
        color: "#FFFF00";
        opacity: 0;
        MouseArea {
            id: rightPanHoverArea;
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape: Qt.SizeHorCursor;
            onEntered: { rightPanning = true; }
            onExited: { rightPanning = false; }
        }        
    }
}
