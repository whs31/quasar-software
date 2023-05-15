import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtLocation 5.15
import QtPositioning 5.15

import Theme 1.0

MapQuickItem {
    z: 50;
//    visible: shown;
    anchorPoint.x: 16;
    anchorPoint.y: 16;
    zoomLevel: 0;
    property real m_opacity: 0.85;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(latitude, longitude);
    sourceItem: Item {
        Pane { id: panel_ImageDialog;
            anchors.left: button_openImageDialog.left;
            anchors.top: button_openImageDialog.top;

            property bool b_Shown: false;
            width: b_Shown ? implicitWidth : 0;
            height: b_Shown ? implicitHeight : 0;
            visible: height > 0;
            enabled: visible;
            Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
            Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
            clip: true;
            Material.background: Theme.color("dark0");
            Material.elevation: 30;

            ColumnLayout {
                Text {
                    font.family: root.mainfont;
                    text: "Изображение №" + Number(index + 1);
                    color: Theme.color("light1");
                    height: 31;
                    font.weight: Font.Bold;
                    font.pixelSize: 16;
                    horizontalAlignment: Text.AlignHCenter;
                    Layout.alignment: Qt.AlignHCenter;
                }

                Row {
                    RoundButton { id: button_HideImage;
                        icon.source: "qrc:/icons/toolbar/map/hidden.png";
                        font.family: root.mainfont;
                        text: shown ? "Скрыть изображение" : "Показать изображение";
                        height: 44;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: Theme.color("dark1");
                        onPressed: shown = !shown;
                    }

                    RoundButton { id: button_DeleteImage;
                        icon.source: "qrc:/icons/toolbar/map/trash.png";
                        font.family: root.mainfont;
                        text: "Удалить изображение";
                        height: 44;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: Theme.color("red");
                        onPressed: deleteImage(index);
                    }
                }
            }
        }

        RoundButton { id: button_openImageDialog;
            icon.source: "qrc:/map/items/image.png";
            height: 44;
            width: 44;
            radius: 15;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            icon.color: Theme.color("light1");
            onPressed: panel_ImageDialog.b_Shown = !panel_ImageDialog.b_Shown;
        }

        Rectangle { id: panel_SARImageTooltip;
            visible: !panel_ImageDialog.b_Shown;
            color: Theme.color("dark1");
            width: (text_ImageIndex.paintedWidth + 5);
            height: (text_ImageIndex.paintedHeight + 3);
            anchors.top: button_openImageDialog.bottom;
            anchors.horizontalCenter: button_openImageDialog.horizontalCenter;
            radius: width / 2;
            Text { id: text_ImageIndex;
                color: Theme.color("light0");
                enabled: true;
                anchors.fill: parent;
                font.pointSize: 8;
                font.family: root.mainfont;
                font.weight: Font.Bold;
                textFormat: Text.RichText;
                text: "\u00A0РЛИ №" + Number(index + 1) + "\u00A0";
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
        }
    }
}
