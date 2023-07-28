import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import QuaSAR.API 1.0

Pane { id: panel_FocusSettings;
    Material.elevation: 30;

    property real focus_ls: 50;
    onFocus_lsChanged: NetworkAPI.execd.setArgument("--ls", focus_ls, Net.Focus);

    property int focus_ni: 10;
    onFocus_niChanged: NetworkAPI.execd.setArgument("--ni", focus_ni, Net.Focus);

    property real focus_vmin: 10;
    onFocus_vminChanged: NetworkAPI.execd.setArgument("--vmin", focus_vmin, Net.Focus);

    property real focus_vmax: 100;
    onFocus_vmaxChanged: NetworkAPI.execd.setArgument("--vmax", focus_vmax, Net.Focus);

    property real focus_px: 0;
    onFocus_pxChanged: NetworkAPI.execd.setArgument("--px", focus_px, Net.Focus);

    property real focus_py: 0;
    onFocus_pyChanged: NetworkAPI.execd.setArgument("--py", focus_py, Net.Focus);

    Behavior on implicitWidth { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }

    ColumnLayout {
        RowLayout {
            Text {
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignVCenter;
                font.family: root.mainfont;
                color: ColorTheme.active.color(ColorTheme.Text)
                font.pixelSize: 14;
                font.weight: Font.DemiBold;
                text: "Размер области для фокусировки  ";
                verticalAlignment: Text.AlignVCenter;
            }

            Slider { id: slider1;
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignLeft;
                from: 10;
                to: 200;
                value: 50;
                onValueChanged: focus_ls = value;
                Material.accent: ColorTheme.active.color(ColorTheme.Orange)
            }

            Text {
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignVCenter;
                font.family: root.mainfont;
                color: ColorTheme.active.color(ColorTheme.Orange)
                font.pixelSize: 14;
                font.weight: Font.DemiBold;
                text: Number(slider1.value).toFixed(0) + " м";
                verticalAlignment: Text.AlignVCenter;
            }
        }

        RowLayout {
            Text {
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignVCenter;
                font.family: root.mainfont;
                color: ColorTheme.active.color(ColorTheme.Text)
                font.pixelSize: 14;
                font.weight: Font.DemiBold;
                text: "Диапазон гипотезы по скорости  ";
                verticalAlignment: Text.AlignVCenter;
            }

            RangeSlider { id: slider2;
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignLeft;
                from: 0;
                to: 300;
                first.value: 10;
                second.value: 100;
                first.onValueChanged: focus_vmin = first.value;
                second.onValueChanged: focus_vmax = second.value;
                Material.accent: ColorTheme.active.color(ColorTheme.Orange)
            }

            Text {
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignVCenter;
                font.family: root.mainfont;
                color: ColorTheme.active.color(ColorTheme.Orange)
                font.pixelSize: 14;
                font.weight: Font.DemiBold;
                text: Number(slider2.first.value).toFixed(0) + " - "
                      + Number(slider2.second.value).toFixed(0) + " км/ч";
                verticalAlignment: Text.AlignVCenter;
            }
        }

        RowLayout {
            Text {
                text: "Гипотезы по скорости  ";
                font {
                    family: root.mainfont;
                    pixelSize: 14;
                }
                color: ColorTheme.active.color(ColorTheme.Text)
                Layout.alignment: Qt.AlignLeft;
            }

            TextField {
                text: "10";
                horizontalAlignment: Text.AlignRight;
                font {
                    family: root.mainfont;
                    pixelSize: 14;
                    bold: true;
                }

                validator: IntValidator {
                    bottom: 0;
                    top: 999;
                }

                Layout.alignment: Qt.AlignRight;
                Material.accent: ColorTheme.active.color(ColorTheme.Orange)

                onEditingFinished: focus_ni = parseInt(text);
            }

            Item {
                width: 20;
                height: 10;
                Layout.fillHeight: true;
            }

            Text {
                text: "Координаты точки: " + Number(focus_px).toFixed(0)
                      + ", " + Number(focus_py).toFixed(0);
                font {
                    family: root.mainfont;
                    pixelSize: 14;
                    bold: true;
                }
                color: ColorTheme.active.color(ColorTheme.Text)
                Layout.alignment: Qt.AlignLeft;
            }
        }
    }
}
