import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtLocation 5.15
import QtPositioning 5.15

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
        RoundButton {
            id: button_openImageDialog
            z: 50
            icon.source: "qrc:/icons/vector/images/image.svg"
            height: 44
            width: 44
            radius: 15
            Material.elevation: 30
            Material.background: theme.base
            icon.color: theme.text
            onPressed: panel_ImageDialog.shown = !panel_ImageDialog.shown
        }

        Pane {
            property bool shown: false//button_ShowTransform.checked

            id: panel_TransformEditor
            anchors {
                right: button_openImageDialog.left
                top: button_openImageDialog.top
            }

            width: shown ? implicitWidth : 0
            height: shown ? implicitHeight : 0
            visible: height > 0
            enabled: visible
            z: 51
            clip: true

            Material.background: theme.base
            Material.elevation: 30

            Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
            Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }

            ColumnLayout {
                Switch {
                    id: enabletransform
                    Layout.fillWidth: true
                    icon.source: "qrc:/icons/vector/images/transform.svg"
                    checked: false
                    font.family: root.mainfont
                    text: "Перемещение изображения"
                }
            }
        }

        Pane {
            property bool shown: false

            id: panel_ImageDialog
            anchors {
                left: button_openImageDialog.right
                top: button_openImageDialog.top
            }

            width: shown ? implicitWidth : 0
            height: shown ? implicitHeight : 0
            visible: height > 0
            enabled: visible
            z: 51
            clip: true

            Material.background: theme.base
            Material.elevation: 30

            Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
            Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }

            ColumnLayout {
                RowLayout {
                    Layout.fillWidth: true

                    Text {
                        font.family: root.mainfont
                        text: "Изображение №" + Number(index + 1)
                        color: theme.text
                        font.weight: Font.Bold
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                        Layout.leftMargin: 36
                    }

                    RoundButton {
                        id: button_CloseDialog
                        z: 50
                        icon.source: "qrc:/icons/vector/common/close.svg"
                        icon.color: theme.base
                        Layout.preferredHeight: 36
                        Layout.preferredWidth: 36
                        height: 36
                        width: 36
                        radius: 18
                        Material.elevation: 30
                        Material.foreground: theme.base
                        Material.background: theme.red
                        onPressed: panel_ImageDialog.shown = !panel_ImageDialog.shown
                    }
                }

                RowLayout {
                    Layout.fillWidth: true

                    RoundButton { id: button_HideImage
                        icon.source: shown ? "qrc:/icons/vector/common/hide.svg"
                                           : "qrc:/icons/vector/common/show.svg"
                        icon.color: theme.text
                        font.family: root.mainfont
                        text: shown ? "Скрыть изображение" : "Показать изображение"
                        height: 40
                        radius: 4
                        Material.elevation: 30
                        Material.background: theme.surface0
                        onPressed: shown = !shown
                    }

                    RoundButton {
                        id: button_DeleteImage
                        Layout.fillWidth: true
                        icon.source: "qrc:/icons/vector/common/delete.svg"
                        icon.color: theme.base
                        font.family: root.mainfont
                        text: "Удалить изображение"
                        height: 40
                        radius: 4
                        Material.elevation: 30
                        Material.foreground: theme.base
                        Material.background: theme.red
                        onPressed: deleteImage(index)
                    }
                }

                RowLayout {
                    Layout.fillWidth: true

                    RoundButton {
                        id: button_ShowControls
                        Layout.fillWidth: true
                        icon.source: "qrc:/icons/vector/common/tune.svg"
                        icon.color: checked ? theme.dark
                                            : theme.text
                        font.family: root.mainfont
                        text: "Параметры"
                        checkable: true
                        checked: false
                        height: 35
                        radius: 4
                        Material.elevation: 30
                        Material.foreground: checked ? theme.base
                                                     : theme.text
                        Material.background: checked ? theme.blue
                                                     : theme.base
                    }

                    RoundButton {
                        id: button_Showmeta
                        icon.source: "qrc:/icons/vector/common/list.svg"
                        icon.color: checked ? theme.base
                                            : theme.text
                        font.family: root.mainfont
                        text: "Метаданные"
                        height: 35
                        radius: 4
                        checkable: true
                        checked: false
                        Material.elevation: 30
                        Material.foreground: checked ? theme.base
                                                     : theme.text
                        Material.background: checked ? theme.blue
                                                     : theme.base
                    }

                    RoundButton {
                        id: button_ShowTransform
                        icon.source: "qrc:/icons/vector/images/transform.svg"
                        icon.color: checked ? theme.base
                                            : theme.text
                        font.family: root.mainfont
                        text: "Геопривязка"
                        height: 35
                        radius: 4
                        checkable: true
                        checked: false
                        Material.elevation: 30
                        Material.foreground: checked ? theme.base
                                                     : theme.text
                        Material.background: checked ? theme.green
                                                     : theme.base
                    }
                }

                ColumnLayout {
                    visible: button_ShowControls.checked
                    spacing: -6
                    Layout.fillWidth: true

                    RoundButton {
                        id: button_EditImage
                        Layout.fillWidth: true
                        Layout.preferredHeight: 35
                        icon.source: "qrc:/icons/vector/common/edit.svg"
                        icon.color: theme.text
                        font.family: root.mainfont
                        text: "Редактирование изображения"
                        height: 35
                        radius: 4
                        Material.elevation: 30
                        Material.background: theme.base
                        onPressed: {
                            c_FocusTab.currentAssignedIndex = index
                            root.openTab(1)
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignVCenter
                            font.family: root.mainfont
                            color: theme.text
                            font.pixelSize: 14
                            font.weight: Font.DemiBold
                            text: "Непрозрачность: "
                            verticalAlignment: Text.AlignVCenter
                        }

                        Slider {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignRight
                            from: 0
                            to: 1
                            value: transparency
                            onValueChanged: transparency = value
                        }
                    }

                    CheckBox {
                        checked: marked_for_export
                        text: "Пометить для экспорта"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: marked_for_export = checked
                    }
                }

                ScrollView {
                    id: layout_Meta
                    Layout.fillWidth: true
                    visible: button_Showmeta.checked
                    implicitHeight: 200
                    clip: true
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                    GridLayout {
                        columns: 2
                        rowSpacing: -2

                        ListModel {
                            id: meta_model
                            Component.onCompleted:
                            {
                                append({str: "Имя файла:", col: theme.text, fill: true});
                                append({str: filename, col: theme.teal, fill: false});
                                append({str: "Широта:", col: theme.text, fill: true});
                                append({str: Number(latitude).toFixed(8) + "°", col: theme.blue, fill: false});
                                append({str: "Долгота:", col: theme.text, fill: true});
                                append({str: Number(longitude).toFixed(8) + "°", col: theme.blue, fill: false});
                                append({str: "Шаг по гор. дальности:",  col: theme.text, fill: true});
                                append({str: Number(dx).toFixed(1),  col: theme.text, fill: false});
                                append({str: "Шаг по путевой дальности:",  col: theme.text, fill: true});
                                append({str: Number(dy).toFixed(1),  col: theme.text, fill: false});
                                append({str: "Ближняя граница по гор. дальности:",  col: theme.text, fill: true});
                                append({str: Number(x0).toFixed(1),  col: theme.text, fill: false});
                                append({str: "Смещение кадра по путевой дальности:",  col: theme.text, fill: true});
                                append({str: Number(y0).toFixed(1),  col: theme.text, fill: false});
                                append({str: "Азимут:",  col: theme.text, fill: true});
                                append({str: Number(angle).toFixed(1) + "°",  col: theme.yellow, fill: false});
                                append({str: "Угол сноса:",  col: theme.text, fill: true});
                                append({str: Number(drift_angle).toFixed(1) + "°",  col: theme.yellow, fill: false});
                                append({str: "Ширина диаграммы направлености:",  col: theme.text, fill: true});
                                append({str: Number(div).toFixed(1) + "°",  col: theme.yellow, fill: false});
                                append({str: "Ширина изображения:",  col: theme.text, fill: true});
                                append({str: Number(lx).toFixed(1) + " px",  col: theme.text, fill: false});
                                append({str: "Высота изображения:",  col: theme.text, fill: true});
                                append({str: Number(ly).toFixed(1) + " px",  col: theme.text, fill: false});
                                append({str: "Скорость носителя:",  col: theme.text, fill: true});
                                append({str: Number(velocity).toFixed(1) + " м/с",  col: theme.mauve, fill: false});
                                append({str: "Высота носителя:",  col: theme.text, fill: true});
                                append({str: Number(altitude).toFixed(1) + " м",  col: theme.mauve, fill: false});
                                append({str: "Коэффициент частотной интерполяции:",  col: theme.text, fill: true});
                                append({str: Number(kr).toFixed(1),  col: theme.teal, fill: false});
                                append({str: "Время сдвига:",  col: theme.text, fill: true});
                                append({str: Number(time_shift).toFixed(1)  + " c",  col: theme.teal, fill: false});
                                append({str: "Время синтезирования:",  col: theme.text, fill: true});
                                append({str: Number(time_duration).toFixed(1)  + " c",  col: theme.teal, fill: false});
                                append({str: "Контрольная сумма:",  col: theme.text, fill: true});
                                append({str: "0x" + Number(crc16).toString(16),  col: theme.peach, fill: false});
                                append({str: "Совпадение CRC:",  col: theme.text, fill: true});
                                append({str: valid ? "ДА" : "НЕТ",  col: valid ? theme.green : theme.red, fill: false});
                            }
                        }

                        Repeater {
                            id: repeater
                            model: meta_model
                            delegate: Text {
                                font.family: root.mainfont
                                font.pixelSize: 12
                                font.bold: !fill
                                Layout.fillWidth: fill
                                Layout.alignment: fill ? Qt.AlignLeft : Qt.AlignRight
                                color: col
                                text: str
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: panel_SARImageTooltip
            visible: !panel_ImageDialog.shown
            color: theme.base
            width: (text_ImageIndex.paintedWidth + 5)
            height: (text_ImageIndex.paintedHeight + 3)
            anchors.top: button_openImageDialog.bottom
            anchors.horizontalCenter: button_openImageDialog.horizontalCenter
            radius: width / 2
            Text { id: text_ImageIndex
                color: theme.text
                enabled: true
                anchors.fill: parent
                font.pointSize: 8
                font.family: root.mainfont
                font.weight: Font.Bold
                textFormat: Text.RichText
                text: "\u00A0РЛИ №" + Number(index + 1) + "\u00A0"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
