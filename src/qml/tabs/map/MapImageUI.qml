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
            icon.source: "qrc:/icons/vector/images/image.svg";
            height: 44;
            width: 44;
            radius: 15;
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            icon.color: ColorTheme.active.color(ColorTheme.Text)
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
            Material.background: ColorTheme.active.color(ColorTheme.Dark)
            Material.elevation: 30;
            z: 51;

            ColumnLayout {
                RowLayout {
                    Text {
                        font.family: root.mainfont;
                        text: "Изображение №" + Number(index + 1);
                        color: ColorTheme.active.color(ColorTheme.Text);
                        font.weight: Font.Bold;
                        font.pixelSize: 16;
                        horizontalAlignment: Text.AlignHCenter;
                        Layout.alignment: Qt.AlignHCenter;
                        Layout.fillWidth: true;
                        Layout.leftMargin: 36;
                    }

                    RoundButton { id: button_CloseDialog;
                        z: 50;
                        icon.source: "qrc:/icons/vector/common/close.svg";
                        icon.color: ColorTheme.active.color(ColorTheme.Dark);
                        Layout.preferredHeight: 36;
                        Layout.preferredWidth: 36;
                        height: 36;
                        width: 36;
                        radius: 18;
                        Material.elevation: 30;
                        Material.foreground: ColorTheme.active.color(ColorTheme.Dark);
                        Material.background: ColorTheme.active.color(ColorTheme.Red);
                        onPressed: panel_ImageDialog.b_Shown = !panel_ImageDialog.b_Shown;
                    }
                }

                Row {
                    RoundButton { id: button_HideImage;
                        icon.source: shown ? "qrc:/icons/vector/common/hide.svg" : "qrc:/icons/vector/common/show.svg";
                        icon.color: ColorTheme.active.color(ColorTheme.Text);
                        font.family: root.mainfont;
                        text: shown ? "Скрыть изображение" : "Показать изображение";
                        height: 40;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: ColorTheme.active.color(ColorTheme.BaseShade);
                        onPressed: shown = !shown;
                    }

                    RoundButton { id: button_DeleteImage;
                        icon.source: "qrc:/icons/vector/common/delete.svg"
                        icon.color: ColorTheme.active.color(ColorTheme.Dark)
                        font.family: root.mainfont
                        text: "Удалить изображение"
                        height: 40
                        radius: 4
                        Material.elevation: 30
                        Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
                        Material.background: ColorTheme.active.color(ColorTheme.Red)
                        onPressed: deleteImage(index)
                    }
                }

                Row {
                    RoundButton { id: button_ShowControls;
                        icon.source: "qrc:/icons/vector/common/tune.svg"
                        icon.color: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                        font.family: root.mainfont;
                        text: "Параметры";
                        checkable: true;
                        checked: false;
                        height: 35;
                        radius: 4;
                        Material.elevation: 30;
                        Material.foreground: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                        Material.background: checked ? ColorTheme.active.color(ColorTheme.PrimaryDark) : ColorTheme.active.color(ColorTheme.BaseShade);
                    }

                    RoundButton { id: button_Showmeta;
                        icon.source: "qrc:/icons/vector/common/list.svg"
                        icon.color: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                        font.family: root.mainfont;
                        text: "Метаданные";
                        height: 35;
                        radius: 4;
                        checkable: true;
                        checked: false;
                        Material.elevation: 30;
                        Material.foreground: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                        Material.background: checked ? ColorTheme.active.color(ColorTheme.PrimaryDark) : ColorTheme.active.color(ColorTheme.BaseShade);
                    }
                }

                ColumnLayout {
                    visible: button_ShowControls.checked;
                    spacing: -6;

                    RoundButton { id: button_EditImage;
                        Layout.fillWidth: true;
                        Layout.preferredHeight: 35;
                        icon.source: "qrc:/icons/vector/common/edit.svg";
                        icon.color: ColorTheme.active.color(ColorTheme.Text);
                        font.family: root.mainfont;
                        text: "Редактирование изображения";
                        height: 35;
                        radius: 4;
                        Material.elevation: 30;
                        Material.background: ColorTheme.active.color(ColorTheme.BaseShade);
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
                            color: ColorTheme.active.color(ColorTheme.Text);
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
                                append({str: "Имя файла:", col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: filename, col: ColorTheme.active.color(ColorTheme.PrimaryDark), fill: false});
                                append({str: "Широта:", col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(latitude).toFixed(8) + "°", col: ColorTheme.active.color(ColorTheme.Primary), fill: false});
                                append({str: "Долгота:", col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(longitude).toFixed(8) + "°", col: ColorTheme.active.color(ColorTheme.Primary), fill: false});
                                append({str: "Шаг по гор. дальности:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(dx).toFixed(1),  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Шаг по путевой дальности:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(dy).toFixed(1),  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Ближняя граница по гор. дальности:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(x0).toFixed(1),  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Смещение кадра по путевой дальности:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(y0).toFixed(1),  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Азимут:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(angle).toFixed(1) + "°",  col: ColorTheme.active.color(ColorTheme.Yellow), fill: false});
                                append({str: "Угол сноса:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(drift_angle).toFixed(1) + "°",  col: ColorTheme.active.color(ColorTheme.Yellow), fill: false});
                                append({str: "Ширина диаграммы направлености:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(div).toFixed(1) + "°",  col: ColorTheme.active.color(ColorTheme.Yellow), fill: false});
                                append({str: "Ширина изображения:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(lx).toFixed(1) + " px",  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Высота изображения:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(ly).toFixed(1) + " px",  col: ColorTheme.active.color(ColorTheme.Text), fill: false});
                                append({str: "Скорость носителя:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(velocity).toFixed(1) + " м/с",  col: ColorTheme.active.color(ColorTheme.Accent), fill: false});
                                append({str: "Высота носителя:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(altitude).toFixed(1) + " м",  col: ColorTheme.active.color(ColorTheme.Accent), fill: false});
                                append({str: "Коэффициент частотной интерполяции:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(kr).toFixed(1),  col: ColorTheme.active.color(ColorTheme.PrimaryLightest), fill: false});
                                append({str: "Время сдвига:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(time_shift).toFixed(1)  + " c",  col: ColorTheme.active.color(ColorTheme.PrimaryLightest), fill: false});
                                append({str: "Время синтезирования:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: Number(time_duration).toFixed(1)  + " c",  col: ColorTheme.active.color(ColorTheme.PrimaryLightest), fill: false});
                                append({str: "Контрольная сумма:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: "0x" + Number(crc16).toString(16),  col: ColorTheme.active.color(ColorTheme.Orange), fill: false});
                                append({str: "Совпадение CRC:",  col: ColorTheme.active.color(ColorTheme.Text), fill: true});
                                append({str: valid ? "ДА" : "НЕТ",  col: valid ? ColorTheme.active.color(ColorTheme.Green) : ColorTheme.active.color(ColorTheme.Red), fill: false});
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
            color: ColorTheme.active.color(ColorTheme.BaseShade);
            width: (text_ImageIndex.paintedWidth + 5);
            height: (text_ImageIndex.paintedHeight + 3);
            anchors.top: button_openImageDialog.bottom;
            anchors.horizontalCenter: button_openImageDialog.horizontalCenter;
            radius: width / 2;
            Text { id: text_ImageIndex;
                color: ColorTheme.active.color(ColorTheme.Text);
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
