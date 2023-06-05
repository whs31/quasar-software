import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

import Theme 1.0

TabButton {
    id: root;
    width: implicitWidth;
    height: implicitHeight;
    display: checked ? TabButton.TextBesideIcon : TabButton.IconOnly;
    leftPadding: 14;
    rightPadding: 14;
    spacing: 10;
    clip: true;
    icon.color: checked ? palette.highlightedText : palette.buttonText;
    font.bold: true;
    palette {
        buttonText: Theme.color("dark2");
        highlight: Theme.color("light0");
        highlightedText: Theme.color("orange");
    }
    contentItem: Item {
        implicitWidth: img.width + (root.spacing + label.contentWidth) * label.visible;
        Image {
            id: img;
            width: root.icon.width / 1.1;
            height: root.icon.height / 1.1;
            anchors {
                left: root.display === TabButton.IconOnly ? undefined : parent.left;
                verticalCenter: parent.verticalCenter;
                horizontalCenter: root.display === TabButton.IconOnly ? parent.horizontalCenter : undefined;
            }
            source: root.icon.source;
            smooth: true;
            antialiasing: true;
            asynchronous: true;

            ColorOverlay {
                anchors.fill: parent;
                source: parent;
                color: root.icon.color;
                cached: true;
                smooth: true;
                antialiasing: true;
            }
        }

        Label {
            id: label;
            anchors {
                topMargin: root.spacing;
                left: img.right;
                leftMargin: root.spacing;
                verticalCenter: parent.verticalCenter;
            }
            text: root.text;
            font: root.font;
            color: root.checked ? root.palette.highlightedText : Qt.darker(root.palette.highlightedText, 1.5);
            visible: root.display !== TabButton.IconOnly;
        }
    }
    background: Rectangle {
        anchors.fill: parent;
        color: root.palette.highlight;
        radius: parent.height * 0.5;
        opacity: root.checked ? 1 : 0.1;
        Behavior on opacity { NumberAnimation { duration: 200; } }
    }

    Behavior on width {
        NumberAnimation {
            duration: 250;
            easing.type: Easing.OutBack;
        }
    }
}
