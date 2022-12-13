import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.15


MapQuickItem {
    //anchors must be set according to 32x32 rescaled image
    //e.g. middle will be QPoint(16, 16);


    //property alias dialogShow: markerDialog.enabled;

    id: marker
    anchorPoint.x: anchorX;
    anchorPoint.y: anchorY;
    z: 2;
    zoomLevel: m_zoom;
    property real m_opacity: 1;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(lat, lon);
    property alias markerName: markerText.text;
    sourceItem: Item {
        Image {
            id: markerSource;
            width: 32;
            height: 32;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: m_qrc;
            visible: true;

            MouseArea {
                id: markerMouseArea;
                propagateComposedEvents: true;
                anchors.fill: parent;
                anchors.topMargin: -20;
                anchors.leftMargin: -20;
                anchors.rightMargin: -20;
                hoverEnabled: true;
                onEntered: {
                    dialogFadeIn.start();
                    markerDialog.enabled = true;
                }
                onExited: {
                    dialogTimer.restart();
                }
            }
        }
        ColorOverlay {
            id: markerOverlay;
            anchors.fill: markerSource;
            source: markerSource;
            opacity: 0.75;
            color: m_color;
        }
        DropShadow {
            anchors.fill: markerOverlay;
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 8.0;
            samples: 17;
            color: "#000000";
            source: markerOverlay;
        }
        Text {
            id: markerText;
            color: markerOverlay.color;
            enabled: true;
            anchors.top: markerSource.bottom;
            anchors.topMargin: 5;
            anchors.horizontalCenter: markerSource.horizontalCenter;
            font.pointSize: 7;
            font.family: "Arial";
            font.weight: Font.Bold;
            textFormat: Text.RichText;
            text: m_name;
        }
        InlineDialog {
            id: markerDialog;
            opacity: 0;
            enabled: true;
            anchors.bottom: markerSource.top;
            anchors.bottomMargin: 2;
            anchors.horizontalCenter: markerSource.horizontalCenter;
            NumberAnimation on opacity {
                id: dialogFadeIn;
                from: 0;
                to: 1;
                duration: 500;
                easing.type: Easing.Linear;
            }
            NumberAnimation on opacity {
                id: dialogFadeOut;
                from: 1;
                to: 0;
                duration: 500;
                easing.type: Easing.Linear;
            }
        }
        Timer { id: dialogTimer; interval: 1000; running: false; onTriggered: {                     dialogFadeOut.start(); markerDialog.enabled = false; }}

    }
}
