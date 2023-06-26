import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0
import Network 1.0
import Filesystem 1.0

import "../../../widgets" as Widgets

Pane { id: panel_ImageTools;
    property bool shown: false;

    height: shown ? implicitHeight : 0;
    visible: height > 0;
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true;
    Material.elevation: 30;

    ColumnLayout {
        Column {
            Layout.fillWidth: true;

            RoundButton { id: button_ImageParams;
                font.family: root.mainfont;
                checkable: true;
                height: 35;
                width: layout_ImageTools.width;
                radius: 4;
                icon.source: "qrc:/icons/google-material/adjust.png";
                icon.color: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                text: "Параметры формирования";
                Material.elevation: 30;
                Material.foreground: checked ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text);
                Material.background: checked ? ColorTheme.active.color(ColorTheme.PrimaryDark) : ColorTheme.active.color(ColorTheme.BaseShade);
            }

            ScrollView { id: scrollview2;
                Layout.fillWidth: true;
                visible: button_ImageParams.checked;
                implicitHeight: 300;
                implicitWidth: parent.width;
                clip: true;
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;

                GridLayout {
                    width: scrollview2.width - 30;
                    columns: 2;
                    columnSpacing: 6;
                    rowSpacing: -4;

                    Text {
                        text: "Смещение по времени, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "1.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("-t", text, Net.Form);
                    }

                    Text {
                        text: "Яркость РЛИ";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }

                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("-b", text, Net.Form);
                    }

                    Text {
                        text: "Высота БПЛА, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "-1";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }

                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("-e", text, Net.Form);
                    }

                    Text {
                        text: "Скорость БПЛА, км/ч";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text)
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "-1";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }

                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("-v", text, Net.Form);
                    }

                    Text {
                        text: "Время синтезирования, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "1.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--Ts", text, Net.Form);
                    }

                    Text {
                        text: "Время записи полосового РЛИ, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "1.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--Tstrip", text, Net.Form);
                    }

                    Text {
                        text: "КЧИ по наклонной дальности";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    RowLayout {
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignRight;

                        Slider { id: slider1;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignLeft;
                            from: 0;
                            to: 4;
                            value: 1;
                            onValueChanged: Network.setArgument("--kR", Number(value).toFixed(0), Net.Form);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: ColorTheme.active.color(ColorTheme.Text);
                            font.pixelSize: 14;
                            font.weight: Font.DemiBold;
                            text: Number(slider1.value).toFixed(0);
                            verticalAlignment: Text.AlignVCenter;
                        }
                    }

                    Text {
                        text: "КЧИ по путевой дальности";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    RowLayout {
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignRight;

                        Slider { id: slider2;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignLeft;
                            from: 0;
                            to: 4;
                            value: 1;
                            onValueChanged: Network.setArgument("--kL", Number(value).toFixed(0), Net.Form);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: ColorTheme.active.color(ColorTheme.Text);
                            font.pixelSize: 14;
                            font.weight: Font.DemiBold;
                            text: Number(slider2.value).toFixed(0);
                            verticalAlignment: Text.AlignVCenter;
                        }
                    }

                    Text {
                        text: "Качество JPEG";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    RowLayout {
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignRight;

                        Slider { id: slider3;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignLeft;
                            from: 1;
                            to: 100;
                            value: 80;
                            onValueChanged: Network.setArgument("--jq", Number(value).toFixed(0), Net.Form);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: ColorTheme.active.color(ColorTheme.Text);
                            font.pixelSize: 14;
                            font.weight: Font.DemiBold;
                            text: Number(slider3.value).toFixed(0);
                            verticalAlignment: Text.AlignVCenter;
                        }
                    }

                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }
                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }


                    Text {
                        text: "Элемент разрешения, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "1.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: {
                            Network.setArgument("--dx", text, Net.Form);
                            Network.setArgument("--dy", text, Net.Form);
                        }
                    }

                    Text {
                        text: "Ближняя граница, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "100.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--x0", text, Net.Form);
                    }

                    Text {
                        text: "Смещение кадра по ПД, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--y0", text, Net.Form);
                    }

                    Text {
                        text: "Протяженность по дальности, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "2000.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--lx", text, Net.Form);
                    }

                    Text {
                        text: "Протяженность по ПД, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "400.0";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        validator: DoubleValidator {
                            decimals: 1;
                            bottom: 0;
                            top: 1000;
                            locale: "en_US";
                        }
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--ly", text, Net.Form);
                    }

                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }
                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }

                    Text {
                        text: "Тип вычислителя";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    ComboBox {
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            weight: Font.Bold;
                        }

                        currentIndex: 0;
                        model: [ "DSP_FFTW", "DSP_CUDA" ];
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;
                        onCurrentValueChanged: Network.setArgument("--DSP", currentValue, Net.Form);
                    }

                    Text {
                        text: "Путь к РЛИ на РЛС";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "./img/";
                        horizontalAlignment: Text.AlignRight;
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            bold: true;
                        }

                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;

                        onEditingFinished: Network.setArgument("--ip", text, Net.Form);
                    }

                    Text {
                        text: "Интерполяция скорости";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    CheckBox {
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            weight: Font.Bold;
                        }

                        checked: false;
                        Layout.alignment: Qt.AlignRight;
                        onCheckedChanged: Network.setArgument("-i", (checked ? "1" : "0"), Net.Form);
                    }

                    Text {
                        text: "Отзеркаливание РЛИ";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: ColorTheme.active.color(ColorTheme.Text);
                        Layout.alignment: Qt.AlignLeft;
                    }

                    CheckBox {
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            weight: Font.Bold;
                        }

                        checked: false;
                        Layout.alignment: Qt.AlignRight;
                        onCheckedChanged: Network.setArgument("--mirror", (checked ? "True" : "False"), Net.Form);
                    }
                }
            }
        }

        Grid { id: layout_ImageTools;
            columns: 2;
            Layout.fillWidth: true;

            RoundButton { id: button_FetchImages;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/refresh.png";
                icon.color: ColorTheme.active.color(ColorTheme.Text);
                text: "Обновить каталог";
                Material.elevation: 30;
                Material.background: Material.background;
                onPressed: {
                    let ret = Filesystem.fetchImageDirectory();
                    if(!ret)
                        messagebox.open("Не найдены изображения", "В целевой папке не найдены радиолокационные изображения.", "warn");
                }

                Widgets.TT { ff: root.mainfont; txt: "Добавить на карту изображения из выбранного каталога"; }
            }

            RoundButton { id: button_ChooseCatalogue;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/folder.png";
                icon.color: ColorTheme.active.color(ColorTheme.Text);
                Material.elevation: 30;
                Material.background: Material.background;
                text: "Изменить каталог";
                onPressed: window_FileDialog.open();

                Widgets.TT { ff: root.mainfont; txt: "Выбрать каталог для добавления изображений на карту"; }
            }

            RoundButton { id: button_ClearLocalCache;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/delete.png";
                icon.color: ColorTheme.active.color(ColorTheme.Dark);
                Material.elevation: 30;
                Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
                Material.background: ColorTheme.active.color(ColorTheme.Red)
                text: "Очистить кэш";
                onPressed: dialogwindow.open("Очистка кэша", "Вы уверены, что хотите очистить кэш радиолокационных изображений? \n" +
                                             "Все изображения, сохраненные на этом АРМ, будут удалены!", "warn", 3);

                Widgets.TT { ff: root.mainfont; txt: "Очистить локальный кэш программы"; }

                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 3 && status === true) {
                            console.log("[GUI] Cache cleared");
                            Paths.clearImageCache();
                        }
                    }
                }
            }
        }
    }
}
