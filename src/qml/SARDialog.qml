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
    z: 2;
    zoomLevel: 0;
    anchorPoint.x: 0;
    anchorPoint.y: 0;
    property real m_opacity: 0.5;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(m_lat, m_lon);
    sourceItem: Rectangle {
        id: sarDialogBase;
        width: childrenRect.width + 10;
        height: childrenRect.height + 10;
        opacity: 0.4
        color: "#22292a";
        radius: 10;
        border.color: "#2a3334";
        z: 100;

//        MouseArea {
//            id: sarDialogMouseArea;
//            propagateComposedEvents: true;
//            anchors.left: sarDialogBase.left;
//            anchors.leftMargin: -5;
//            anchors.right: sarDialogBase.right;
//            anchors.rightMargin: -5;
//            anchors.bottom: sarDialogBase.bottom;
//            anchors.bottomMargin: -5;
//            anchors.top: sarDialogBase.top;
//            anchors.topMargin: -5;
//            hoverEnabled: true;
//            onEntered: {
//                //sardialogFadeIn.start();
//                sarUI.visible = true;
//                //sarUI.enabled = true;
//            }
//            onExited: {
//                //sardialogFadeOut.start();
//                //markerDialog.visible = false;
//                //sarUI.enabled = false;
//                //dialogTimer.start();
//            }
//            Rectangle { //hitbox
//                anchors.fill: parent
//                color: "#FF00FF";
//                visible: false;
//            }
//        }
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
    NumberAnimation on opacity {
        id: sardialogFadeIn;
        from: 0;
        to: 1;
        duration: 300;
        easing.type: Easing.Linear;
    }
    NumberAnimation on opacity {
        id: sardialogFadeOut;
        from: 1;
        to: 0;
        duration: 300;
        easing.type: Easing.Linear;
    }
}
