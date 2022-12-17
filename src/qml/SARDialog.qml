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
    anchorPoint.x: 24;
    anchorPoint.y: 24;
    property real m_opacity: 1;
    opacity: m_opacity;
    property real m_scale: 1;
    scale: m_scale;
    coordinate: QtPositioning.coordinate(m_lat, m_lon);
    sourceItem: Item {
        Image {
            id: radarImage;
            width: 48;
            height: 48;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: "qrc:/map-resources/markers/radar.png";
            visible: true;
        }

        MouseArea {
                id: radarImageMouseArea;
                propagateComposedEvents: true;
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
                font.pointSize: 8;
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
            Column {
            id: column
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 5;
            anchors.topMargin: 5;

            Text {
                id: text1
                color: "#fff5ee"
                text: qsTr("Информация об изображении")
                font.pixelSize: 9
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.underline: true
                font.bold: true
            }

            Text {
                id: text3
                color: "#fff5ee"
                text: qsTr("Имя файла: ") + m_filename;
                font.pixelSize: 8
                fontSizeMode: Text.FixedSize
                font.bold: true
            }

            Text {
                id: text4
                color: "#fff5ee"
                text: qsTr("Дата: ") + m_datetime;
                font.pixelSize: 8
                font.bold: true
            }

            Text {
                id: text5
                color: "#fff5ee"
                text: qsTr("Совпадение хэша: ") + m_checksumMatch;
                font.pixelSize: 8
                font.bold: true
            }

            Text {
                id: text6
                color: "#fff5ee"
                text: qsTr("Широта: ") + m_latitude;
                font.pixelSize: 8
                font.bold: true
            }

            Text {
                id: text7
                color: "#fff5ee"
                text: qsTr("Долгота: ") + m_longitude;
                font.pixelSize: 8
                font.bold: true
            }

            Text {
                id: text8
                color: "#fff5ee"
                text: qsTr("dx: ") + m_dx;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text9
                color: "#fff5ee"
                text: qsTr("dy: ") + m_dy;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text10
                color: "#fff5ee"
                text: qsTr("x0: ") + m_x0;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text11
                color: "#fff5ee"
                text: qsTr("y0: ") + m_y0;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text12
                color: "#fff5ee"
                text: qsTr("Тета-азимут: ") + m_azimuth;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text13
                color: "#fff5ee"
                text: qsTr("Угол сноса: ") + m_driftAngle;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text14
                color: "#fff5ee"
                text: qsTr("Угол поворота: ") + m_angle;
                font.pixelSize: 8
                font.italic: true
            }

            Text {
                id: text15
                color: "#fff5ee"
                text: qsTr("Хэш файла: ") + m_hash;
                font.pixelSize: 8
                font.italic: true
            }
            }
        }
    }
    onAnimChanged: {
        if(anim === true) { sardialogFadeIn.start(); sarDialogBase.enabled = true; sarDialogBase.visible = true;}
        else { sardialogFadeOut.start(); sarDialogBase.enabled = false; }
    }   
}
