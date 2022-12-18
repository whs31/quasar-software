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
    id: sarUI;  
    property bool anim: m_visible;
    
    z: 2;
    zoomLevel: 0;
    anchorPoint.x: 18;
    anchorPoint.y: 18;
    property real m_opacity: 0.8;
    opacity: m_opacity;
    property real m_scale: 1;
    scale: m_scale;
    coordinate: QtPositioning.coordinate(m_lat, m_lon);
    sourceItem: Item {
        Image {
            id: radarImage;
            width: 36;
            height: 36;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: "qrc:/map-resources/markers/radar.png";
            visible: true;
        }

        MouseArea {
                id: radarImageMouseArea;
                propagateComposedEvents: true;
                cursorShape: Qt.WhatsThisCursor;
                anchors.left: radarImage.left;
                anchors.leftMargin: -5;
                anchors.right: radarImage.right;
                anchors.rightMargin: -5;
                anchors.bottom: radarImage.bottom;
                anchors.bottomMargin: -5;
                anchors.top: radarImage.top;
                anchors.topMargin: -5;
                //hoverEnabled: true;
                onClicked: {
                    anim = !anim;
                }
            }
        ColorOverlay {
            id: radarImageOverlay;
            anchors.fill: radarImage;
            source: radarImage;
            opacity: 0.75;
            color: "#fff5ee";
        }
        DropShadow {
            anchors.fill: radarImageOverlay;
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 8.0;
            samples: 17;
            color: "#000000";
            source: radarImageOverlay;
        }
        Rectangle {
            id: textOverlay;
            color: "#fff5ee";
            width: radarImageText.paintedWidth + 10;
            height: radarImageText.paintedHeight + 3;
            anchors.top: radarImage.bottom;
            anchors.topMargin: 5;
            anchors.horizontalCenter: radarImage.horizontalCenter;
            radius: 10
            Text {
                id: radarImageText;
                color: "#121212"; //radarImageOverlay.color;
                enabled: true;
                anchors.fill: parent;
                font.pointSize: 7;
                font.family: "Arial";
                font.weight: Font.Bold;
                textFormat: Text.RichText;
                text: "Изображение №" + Number(index + 1);
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
        }

        Rectangle {
            id: sarDialogBase;
            width: childrenRect.width + 10;
            height: childrenRect.height + 10;
            anchors.left: textOverlay.right;
            anchors.leftMargin: 10;
            opacity: 0;
            color: "#132623";
            radius: 10;
            border.color: "#204040";
            z: 100;
            Component.onCompleted:
            {
                visible = false;
                console.log(anim);
            }
            NumberAnimation on opacity {
                id: sardialogFadeIn;
                from: 0;
                to: 0.8;
                duration: 300;
                easing.type: Easing.Linear;
            }
            NumberAnimation on opacity {
                id: sardialogFadeOut;
                from: 0.8;
                to: 0;
                duration: 300;
                easing.type: Easing.Linear;
            }
            Text {
                id: text_d_infoLabel;
                color: "#dae1e5";
                text: "Информация об изображении";
                font.pixelSize: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 4;
                anchors.top: parent.top;
                anchors.topMargin: 4;
                horizontalAlignment: Text.AlignLeft;
                verticalAlignment: Text.AlignTop;
                font.underline: true;
                font.bold: true;
            }
            SARDialogMetadataText {
                id: metadataColumn;
                anchors.left: text_d_infoLabel.left;
                anchors.top: text_d_infoLabel.bottom;
                anchors.topMargin: 3;
            }
        }
    }
    onAnimChanged: {
        if(anim === true) { sardialogFadeIn.start(); sarDialogBase.enabled = true; sarDialogBase.visible = true;}
        else { sardialogFadeOut.start(); sarDialogBase.enabled = false; }
    }   
}
