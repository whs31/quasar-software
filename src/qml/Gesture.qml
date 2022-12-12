import QtQuick 2.12

Item {
    Rectangle {
            id: bottomPan;
            anchors.left: parent.left;
            anchors.leftMargin: 40;
            anchors.right: parent.right;
            anchors.rightMargin: 40;
            anchors.bottom: parent.bottom;
            height: 40;
            color: "#FF0000";
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
            anchors.left: parent.left;
            anchors.leftMargin: 40;
            anchors.right: parent.right;
            anchors.rightMargin: 40;
            anchors.top: parent.top;
            height: 40;
            color: "#FF0000";
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
            anchors.top: parent.top;
            anchors.topMargin: 40;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 40;
            width: 40;
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
            anchors.top: parent.top;
            anchors.topMargin: 40;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 40;
            width: 40;
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
