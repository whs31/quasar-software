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
    sourceItem: Item { z: 50;
        RoundButton { id: button_openImageDialog;
            z: 50;
            icon.source: "qrc:/map/items/image.png";
            height: 44;
            width: 44;
            radius: 15;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            icon.color: Theme.color("light1");
            onPressed: panel_ImageDialog.b_Shown = !panel_ImageDialog.b_Shown;
        }

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
            z: 51;

            ColumnLayout {
                RowLayout {
                    Text {
                        font.family: root.mainfont;
                        text: "Изображение №" + Number(index + 1);
                        color: Theme.color("light1");
                        font.weight: Font.Bold;
                        font.pixelSize: 16;
                        horizontalAlignment: Text.AlignHCenter;
                        Layout.alignment: Qt.AlignHCenter;
                        Layout.fillWidth: true;
                        Layout.leftMargin: 36;
                    }

                    RoundButton { id: button_CloseDialog;
                        z: 50;
                        icon.source: "qrc:/icons/google-material/close.png";
                        icon.color: Theme.color("dark0");
                        Layout.preferredHeight: 36;
                        Layout.preferredWidth: 36;
                        height: 36;
                        width: 36;
                        radius: 18;
                        Material.elevation: 30;
                        Material.foreground: Theme.color("dark0");
                        Material.background: Theme.color("red");
                        onPressed: panel_ImageDialog.b_Shown = !panel_ImageDialog.b_Shown;
                    }
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
                        icon.color: Theme.color("dark0");
                        font.family: root.mainfont;
                        text: "Удалить изображение";
                        height: 40;
                        radius: 4;
                        Material.elevation: 30;
                        Material.foreground: Theme.color("dark0");
                        Material.background: Theme.color("red");
                        onPressed: deleteImage(index);
                    }
                }

                Row {
                    RoundButton { id: button_ShowControls;
                        icon.source: "qrc:/icons/google-material/adjust.png";
                        icon.color: checked ? Theme.color("dark0") : Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Параметры";
                        checkable: true;
                        checked: false;
                        height: 35;
                        radius: 4;
                        Material.elevation: 30;
                        Material.foreground: checked ? Theme.color("dark0") : Theme.color("light0");
                        Material.background: checked ? Theme.color("color0") : Theme.color("dark1");
                    }

                    RoundButton { id: button_Showmeta;
                        icon.source: "qrc:/icons/google-material/list.png";
                        icon.color: checked ? Theme.color("dark0") : Theme.color("light0");
                        font.family: root.mainfont;
                        text: "Метаданные";
                        height: 35;
                        radius: 4;
                        checkable: true;
                        checked: false;
                        Material.elevation: 30;
                        Material.foreground: checked ? Theme.color("dark0") : Theme.color("light0");
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
                        onPressed: {
                            c_FocusTab.currentAssignedIndex = index;
                            root.openTab(1);
                        }
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

                    CheckBox {
                        checked: marked_for_export;
                        text: "Пометить для экспорта";
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        onCheckedChanged: marked_for_export = checked;
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
                        rowSpacing: -2;

                        ListModel { id: meta_model
                            Component.onCompleted:
                            {
                                append({str: "Имя файла:", col: Theme.color("light0"), fill: true});
                                append({str: filename, col: Theme.color("color0"), fill: false});
                                append({str: "Широта:", col: Theme.color("light0"), fill: true});
                                append({str: Number(latitude).toFixed(8) + "°", col: Theme.color("color1"), fill: false});
                                append({str: "Долгота:", col: Theme.color("light0"), fill: true});
                                append({str: Number(longitude).toFixed(8) + "°", col: Theme.color("color1"), fill: false});
                                append({str: "Шаг по гор. дальности:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(dx).toFixed(1),  col: Theme.color("light0"), fill: false});
                                append({str: "Шаг по путевой дальности:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(dy).toFixed(1),  col: Theme.color("light0"), fill: false});
                                append({str: "Ближняя граница по гор. дальности:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(x0).toFixed(1),  col: Theme.color("light0"), fill: false});
                                append({str: "Смещение кадра по путевой дальности:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(y0).toFixed(1),  col: Theme.color("light0"), fill: false});
                                append({str: "Азимут:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(angle).toFixed(1) + "°",  col: Theme.color("yellow"), fill: false});
                                append({str: "Угол сноса:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(drift_angle).toFixed(1) + "°",  col: Theme.color("yellow"), fill: false});
                                append({str: "Ширина диаграммы направлености:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(div).toFixed(1) + "°",  col: Theme.color("yellow"), fill: false});
                                append({str: "Ширина изображения:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(lx).toFixed(1) + " px",  col: Theme.color("light0"), fill: false});
                                append({str: "Высота изображения:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(ly).toFixed(1) + " px",  col: Theme.color("light0"), fill: false});
                                append({str: "Скорость носителя:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(velocity).toFixed(1) + " м/с",  col: Theme.color("accent"), fill: false});
                                append({str: "Высота носителя:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(altitude).toFixed(1) + " м",  col: Theme.color("accent"), fill: false});
                                append({str: "Коэффициент частотной интерполяции:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(kr).toFixed(1),  col: Theme.color("color3"), fill: false});
                                append({str: "Время сдвига:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(time_shift).toFixed(1)  + " c",  col: Theme.color("color3"), fill: false});
                                append({str: "Время синтезирования:",  col: Theme.color("light0"), fill: true});
                                append({str: Number(time_duration).toFixed(1)  + " c",  col: Theme.color("color3"), fill: false});
                                append({str: "Контрольная сумма:",  col: Theme.color("light0"), fill: true});
                                append({str: "0x" + Number(crc16).toString(16),  col: Theme.color("orange"), fill: false});
                                append({str: "Совпадение CRC:",  col: Theme.color("light0"), fill: true});
                                append({str: valid ? "ДА" : "НЕТ",  col: valid ? Theme.color("green") : Theme.color("red"), fill: false});
                            }
                        }

                        Repeater { id: repeater
                            model: meta_model;
                            delegate: Text {
                                font.family: root.mainfont
                                font.pixelSize: 12
                                font.bold: !fill;
                                Layout.fillWidth: fill;
                                Layout.alignment: fill ? Qt.AlignLeft : Qt.AlignRight;
                                color: col;
                                text: str;
                            }
                        }
                    }
                }
            }
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
