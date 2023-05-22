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
    sourceItem: Item { z: 60;
        Pane { id: panel_ImageDialog;
            anchors.left: button_openImageDialog.right;
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
                    font.weight: Font.Bold;
                    font.pixelSize: 15;
                    horizontalAlignment: Text.AlignHCenter;
                    Layout.alignment: Qt.AlignHCenter;
                }

                Row {
                    RoundButton { id: button_HideImage;
                        icon.source: "qrc:/icons/google-material/hide.png";
                        icon.color: Theme.color("light0");
                        font.family: root.mainfont;
                        text: shown ? "Скрыть изображение" : "Показать изображение";
                        height: 40;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: Theme.color("dark1");
                        onPressed: shown = !shown;
                    }

                    RoundButton { id: button_DeleteImage;
                        icon.source: "qrc:/icons/google-material/delete.png";
                        icon.color: Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Удалить изображение";
                        height: 40;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: Theme.color("red");
                        onPressed: deleteImage(index);
                    }
                }

                Row {
                    RoundButton { id: button_ShowControls;
                        icon.source: "qrc:/icons/google-material/adjust.png";
                        icon.color: Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Параметры";
                        checkable: true;
                        checked: false;
                        height: 35;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: checked ? Theme.color("color0") : Theme.color("dark1");
                    }

                    RoundButton { id: button_Showmeta;
                        icon.source: "qrc:/icons/google-material/list.png";
                        icon.color: Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Метаданные";
                        height: 35;
                        radius: 4;
                        checkable: true;
                        checked: false;
                        Material.elevation: 30;
                        Material.background: checked ? Theme.color("color0") : Theme.color("dark1");
                    }
                }

                ColumnLayout {
                    visible: button_ShowControls.checked;
                    spacing: -6;

                    RoundButton { id: button_EditImage;
                        Layout.fillWidth: true;
                        Layout.preferredHeight: 35;
                        icon.source: "qrc:/icons/google-material/edit.png";
                        icon.color: Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Редактирование изображения";
                        height: 35;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: Theme.color("dark1");
                        //onPressed:
                    }

                    RowLayout {
                        Layout.fillWidth: true;
                        Text {
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 14;
                            font.weight: Font.DemiBold;
                            text: "Непрозрачность: ";
                            verticalAlignment: Text.AlignVCenter;
                        }

                        Slider {
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignRight;
                            from: 0;
                            to: 1;
                            value: transparency;
                            onValueChanged: transparency = value;
                        }
                    }
                }

                ScrollView {id: layout_Meta;
                    Layout.fillWidth: true;
                    visible: button_Showmeta.checked;
                    implicitHeight: 200;
                    clip: true;
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn;

                    GridLayout {
                        columns: 2;
                        columnSpacing: -6;
                        rowSpacing: -4;

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Имя файла:";
                            Layout.fillWidth: true;
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: filename;
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Широта:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color1");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(latitude).toFixed(8) + "°";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Долгота:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color1");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(longitude).toFixed(8) + "°";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Шаг по гор. дальности:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(dx).toFixed(1);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Шаг по путевой дальности:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(dy).toFixed(1);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Ближняя граница по гор. дальности:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(x0).toFixed(1);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Смещение кадра по путевой дальности:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(y0).toFixed(1);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Азимут:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("yellow");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(angle).toFixed(1) + "°";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Угол сноса:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("yellow");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(drift_angle).toFixed(1) + "°";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Ширина диаграммы направлености:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("yellow");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(div).toFixed(1) + "°";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Ширина изображения:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(lx).toFixed(1) + " px";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Высота изображения:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(ly).toFixed(1) + " px";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Скорость носителя:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("accent");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(velocity).toFixed(1) + " м/с";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Высота носителя:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("accent");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(altitude).toFixed(1) + " м";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Коэффициент частотной интерполяции:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color3");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(kr).toFixed(1);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Время сдвига:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color3");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(time_shift).toFixed(1)  + " c";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Время синтезирования:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("color3");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(time_duration).toFixed(1)  + " c";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Режим:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: Number(mode);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Контрольная сумма:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("orange");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: "0x" + Number(crc16).toString(16);
                        }

                        Text {
                            font.family: root.mainfont;
                            color: Theme.color("light0");
                            font.pixelSize: 12;
                            text: "Совпадение CRC:";
                        }

                        Text {
                            font.family: root.mainfont;
                            color: valid ? Theme.color("green") : Theme.color("red");
                            font.pixelSize: 12;
                            font.bold: true;
                            Layout.alignment: Qt.AlignRight;
                            text: valid ? "ДА" : "НЕТ";
                        }
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
