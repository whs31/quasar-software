import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import RadarDiagram 1.0

Pane { id: panel_Parameters;
    property bool shown: false;

    height: shown ? implicitHeight : 0;
    visible: height > 0;
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true;
    Material.elevation: 30;

    ColumnLayout {
        spacing: -4;

        RowLayout {
            Text {
                font.family: root.mainfont;
                font.weight: Font.DemiBold;
                font.pixelSize: 14;
                color: ColorTheme.active.color(ColorTheme.Text)
                text: "Режим карты   ";
                Layout.alignment: Qt.AlignLeft;
            }

            ComboBox {
                font.family: root.mainfont;
                font.weight: Font.Bold;
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                currentIndex: 2;
                model: ["Оффлайн-карта", "Схема", "Спутник", "Гибрид"];

                onCurrentValueChanged: {
                    if(currentValue === "Оффлайн-карта")
                        i_MapMode = 0;
                    if(currentValue === "Схема")
                        i_MapMode = 5;
                    if(currentValue === "Спутник")
                        i_MapMode = 1;
                    if(currentValue === "Гибрид")
                        i_MapMode = 4;
                }
            }
        }

        CheckBox { id: checkbox_ShowCursorCoords;
            font.family: root.mainfont;
            checked: true;
            text: "Отображать координаты курсора";
            onCheckedChanged: coord_tooltip.visible = checked;
        }

        CheckBox { id: checkbox_ShowTrack;
            font.family: root.mainfont;
            checked: true;
            text: "Отображать трек полёта";
            onCheckedChanged: c_Route.opacity = checked ? 1 : 0;
        }

        RowLayout {
            Text {
                font.family: root.mainfont;
                font.weight: Font.DemiBold;
                font.pixelSize: 14;
                color: ColorTheme.active.color(ColorTheme.Text)
                text: "Тип трека   ";
                Layout.alignment: Qt.AlignLeft;
            }

            ComboBox {
                font.family: root.mainfont;
                font.weight: Font.Bold;
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                currentIndex: 1;
                model: ["Полный", "Частичный"];

                onCurrentValueChanged: {
                    if(currentValue === "Полный")
                        routeType = 0;
                    if(currentValue === "Частичный")
                        routeType = 1;
                }
            }
        }

        Column {
            Layout.fillWidth: true;

            RoundButton { id: button_ClearTrack;
                radius: 4;
                icon.source: "qrc:/icons/google-material/clear.png";
                icon.color: ColorTheme.active.color(ColorTheme.Dark)
                height: 40;
                font.family: root.mainfont;
                width: checkbox_ShowDiagram.width;
                text: "Очистить трек полёта";
                Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
                Material.background: ColorTheme.active.color(ColorTheme.Red)
                onPressed: dialogwindow.open("Очистка трека", "Вы уверены, что хотите очистить трек полёта?", "warn", 1);
                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 1 && status === true) {
                            console.log("[GUI] Track cleared");
                            c_Route.clear();
                        }
                    }
                }
            }
        }

        Item { Layout.fillHeight: true; Layout.fillWidth: true; height: 15; }

        CheckBox { id: checkbox_ShowDiagram;
            font.family: root.mainfont;
            checked: true;
            text: "Отображать диаграмму направленности";
            onCheckedChanged: c_RadarDiagramView.shown = checked;
        }

        RowLayout {
            Text {
                font.family: root.mainfont;
                font.weight: Font.DemiBold;
                font.pixelSize: 14;
                color: ColorTheme.active.color(ColorTheme.Text)
                text: "Тип диаграммы   ";
                Layout.alignment: Qt.AlignLeft;
            }

            ComboBox {
                font.family: root.mainfont;
                font.weight: Font.Bold;
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                currentIndex: 0;
                model: ["Телескопическая", "Полосовая"];

                onCurrentValueChanged: {
                    if(currentValue === "Телескопическая")
                        c_RadarDiagram.type = RadarDiagram.Telescopic;
                    if(currentValue === "Полосовая")
                        c_RadarDiagram.type = RadarDiagram.Strip;
                }
            }
        }
    }
}

