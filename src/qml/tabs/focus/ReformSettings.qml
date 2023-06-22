import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0

Pane { id: panel_ReformSettings;
    function setVelocityAndElevation(vel, ele)
    {
        input_velocity.text = vel;
        input_elevation.text = ele;
        Network.setArgument("-v", input_velocity.text, Net.Reform);
        Network.setArgument("-v", input_velocity.text, Net.Focus);
        Network.setArgument("-e", input_elevation.text, Net.Reform);
        Network.setArgument("-e", input_elevation.text, Net.Focus);
    }

    clip: true;
    width: parent.width;
    height: parent.height;
    Material.elevation: 30;

    ColumnLayout { id: layout_reform;
        width: parent.width;
        clip: true;

        Column {
            Layout.fillWidth: true;

            ScrollView { id: scrollview2;
                Layout.fillHeight: true
                implicitHeight: panel_ReformSettings.height - 100;
                clip: true;
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;

                GridLayout { id: grid_layout1;
                    columns: 2;
                    columnSpacing: 6;
                    rowSpacing: -4;

                    Text {
                        text: "Режим формирования";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
                        Layout.alignment: Qt.AlignLeft;
                    }

                    ComboBox {
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                            weight: Font.Bold;
                        }

                        currentIndex: 0;
                        model: [ "М1 телескопический", "М2 телескопический", "М3 телескопический", "М4 телескопический",
                                 "М6 телескопический", "М7 телескопический", ];
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;
                        onCurrentValueChanged: {
                            let val = (currentIndex + 1);
                            if(val === 6)
                                val = 7;
                            if(val === 5)
                                val = 6;
                            Network.setArgument("-m", val, Net.Reform);
                        }
                    }

                    Text {
                        text: "Смещение по времени, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("-t", text, Net.Reform);
                    }

                    Text {
                        text: "Яркость РЛИ";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: {
                            Network.setArgument("-b", text, Net.Reform);
                            Network.setArgument("-b", text, Net.Focus);
                        }
                    }

                    Text {
                        text: "Высота БПЛА, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: input_elevation;
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

                        onEditingFinished: {
                            Network.setArgument("-e", text, Net.Reform);
                            Network.setArgument("-e", text, Net.Focus);
                        }
                    }

                    Text {
                        text: "Скорость БПЛА, км/ч";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: input_velocity;
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

                        onEditingFinished: {
                            Network.setArgument("-v", text, Net.Reform);
                            Network.setArgument("-v", text, Net.Focus);
                        }
                    }

                    Text {
                        text: "Время синтезирования, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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
                            Network.setArgument("--Ts", text, Net.Reform);
                            Network.setArgument("--Ts", text, Net.Focus);
                        }
                    }

                    Text {
                        text: "Время записи полосового РЛИ, с";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--Tstrip", text, Net.Reform);
                    }

                    Text {
                        text: "КЧИ по наклонной дальности";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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
                            onValueChanged: Network.setArgument("--kR", Number(value).toFixed(0), Net.Reform);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: Theme.color("light0");
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
                        color: Theme.color("light1");
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
                            onValueChanged: Network.setArgument("--kL", Number(value).toFixed(0), Net.Reform);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: Theme.color("light0");
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
                        color: Theme.color("light1");
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
                            onValueChanged: Network.setArgument("--jq", Number(value).toFixed(0), Net.Reform);
                        }

                        Text {
                            Layout.fillHeight: true;
                            Layout.alignment: Qt.AlignVCenter;
                            font.family: root.mainfont;
                            color: Theme.color("light0");
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
                        color: Theme.color("light1");
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
                            Network.setArgument("--dx", text, Net.Reform);
                            Network.setArgument("--dy", text, Net.Reform);
                        }
                    }

                    Text {
                        text: "Ближняя граница, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--x0", text, Net.Reform);
                    }

                    Text {
                        text: "Смещение кадра по ПД, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--y0", text, Net.Reform);
                    }

                    Text {
                        text: "Протяженность по дальности, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--lx", text, Net.Reform);
                    }

                    Text {
                        text: "Протяженность по ПД, м";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--ly", text, Net.Reform);
                    }

                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }
                    Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 20; }

                    Text {
                        text: "Тип вычислителя";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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
                        onCurrentValueChanged: Network.setArgument("--DSP", currentValue, Net.Reform);
                    }

                    Text {
                        text: "Путь к РЛИ на РЛС";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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

                        onEditingFinished: Network.setArgument("--ip", text, Net.Reform);
                    }

                    Text {
                        text: "Интерполяция скорости";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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
                        onCheckedChanged: Network.setArgument("-i", (checked ? "1" : "0"), Network.Reform);
                    }

                    Text {
                        text: "Отзеркаливание РЛИ";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
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
                        onCheckedChanged: Network.setArgument("--mirror", (checked ? "True" : "False"), Net.Reform);
                    }
                }
            }
        }
    }
}
