import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0
import Network 1.0
import Filesystem 1.0

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
            RoundButton { id: button_FormImage;
                font.family: root.mainfont;
                height: 40;
                width: layout_ImageTools.width;
                radius: 4;
                icon.source: "qrc:/icons/google-material/take-photo.png";
                icon.color: Theme.color("dark0");
                text: "Формирование изображения";
                Material.elevation: 30;
                Material.foreground: Theme.color("dark0");
                Material.background: Theme.color("accent");
                onPressed: Network.executeCommand(Network.FormImage);
            }

            RoundButton { id: button_ImageParams;
                font.family: root.mainfont;
                checkable: true;
                height: 35;
                width: layout_ImageTools.width;
                radius: 4;
                icon.source: "qrc:/icons/google-material/adjust.png";
                icon.color: checked ? Theme.color("dark0") : Theme.color("light0");
                text: "Параметры формирования";
                Material.elevation: 30;
                Material.foreground: checked ? Theme.color("dark0") : Theme.color("light0");
                Material.background: checked ? Theme.color("color0") : Theme.color("dark1");
            }

            ScrollView { id: scrollview2;
                Layout.fillWidth: true;
                visible: button_ImageParams.checked;
                implicitHeight: 300;
                implicitWidth: parent.width;
                clip: true;
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn;

                GridLayout {
                    width: scrollview2.width - 10;
                    columns: 2;
                    columnSpacing: 6;
                    rowSpacing: -4;

                    Text {
                        text: "Режим формирования:";
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
                        // for some reason it's broken
//                        currentIndex: (parseInt(Network.argument("-m", Network.Form) - 1)) > 3
//                                            ? parseInt(Network.argument("-m", Network.Form) - 1)
//                                            : parseInt(Network.argument("-m", Network.Form) - 2);
                        currentIndex: 0;
                        model: [ "Телескопический М1", "Телескопический M2", "Телескопический M3", "Телескопический M4",
                                 "Телескопический M6", "Телескопический M7", ];
                        Layout.alignment: Qt.AlignRight;
                        Layout.fillWidth: true;
                        onCurrentValueChanged: {
                            let val = (currentIndex + 1);
                            if(val === 6)
                                val = 7;
                            if(val === 5)
                                val = 6;
                            Network.setArgument("-m", val, Network.Form);
                        }
                    }

                    Text {
                        text: "Смещение по времени:";
                        font {
                            family: root.mainfont;
                            pixelSize: 14;
                        }
                        color: Theme.color("light1");
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField {
                        text: "1.0";
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

                        onEditingFinished: Network.setArgument("-t", text, Network.Form);
                    }

                    /*
                    {"-b", ExecdArgument(0.0f)},            //! @var Яркость РЛИ, 0 - авто [0 - inf]
                    {"-e", ExecdArgument(-1.0f)},           //! @var Высота БПЛА отн. уровня моря, -1 - авто, м
                    {"-v", ExecdArgument(-1.0f)},           //! @var Скорость БПЛА, -1 - авто, км/ч
                    {"-i", ExecdArgument(0)},               //! @var Интерполяция скорости [0, 1] - 0: среднее значение за Ts,
                                                            //!      1: интерполированное значение для каждого периода за Ts
                    {"--Ts", ExecdArgument(1.0f)},          //! @var Время синтезирования апертуры антенны [0 - inf]
                    {"--Tstrip", ExecdArgument(1.0f)},      //! @var Время формирования полосового РЛИ [0 - inf]
                    {"--kR", ExecdArgument(1)},             //! @var Коэффициент частотной интерполяции по наклонной дальности [1..4]
                    {"--kL", ExecdArgument(1)},             //! @var Коэффициент частотной интерполяции по путевой дальности [1..4]
                    {"--jq", ExecdArgument(80)},            //! @var Качество РЛИ после компрессии JPEG [1..100]

                    {"--dx", ExecdArgument(1.0f)},          //! @var Размер элемента разрешения РЛИ по дальности, м [0 - inf]
                    {"--dy", ExecdArgument(1.0f)},          //! @var Размер элемента разрешения РЛИ по путевой дальности, м [0 - inf]
                    {"--x0", ExecdArgument(100.0f)},        //! @var Расстояние до ближней границы РЛИ, м [0 - inf]
                    {"--y0", ExecdArgument(0.0f)},          //! @var Смещение кадра РЛИ по путевой дальности, м [0 - inf]
                    {"--lx", ExecdArgument(2'000.0f)},      //! @var Протяженность РЛИ по дальности, м [0 - inf]
                    {"--ly", ExecdArgument(400.0f)},        //! @var Протяженность РЛИ по путевой дальности, м [0 - inf]
                    {"--ip", ExecdArgument("./img/")},      //! @var Путь для сохранения РЛИ на РЛС
                    {"--remote", ExecdArgument("None")},    //! @var IP-адрес сервера TCP для передачи РЛИ (e.g. 127.0.0.1:9955)
                    {"--DSP", ExecdArgument("DSP_FFTW")},   //! @var Тип вычислителя [DSP_FFTW, DSP_CUDA]
                    {"--mirror", ExecdArgument("False")},   //! @var Вертикальное отзеркаливание РЛИ [True, False]
                    */
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
                icon.color: Theme.color("light0");
                text: "Обновить каталог";
                Material.elevation: 30;
                Material.background: Material.background;
                onPressed: {
                    let ret = Filesystem.fetchImageDirectory();
                    if(!ret)
                        messagebox.open("Не найдены изображения", "В целевой папке не найдены радиолокационные изображения.", "warn");
                }
            }

            RoundButton { id: button_ChooseCatalogue;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/folder.png";
                icon.color: Theme.color("light0");
                Material.elevation: 30;
                Material.background: Material.background;
                text: "Изменить каталог";
                onPressed: window_FileDialog.open();
            }

            RoundButton { id: button_ClearLocalCache;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/delete.png";
                icon.color: Theme.color("dark0");
                Material.elevation: 30;
                Material.foreground: Theme.color("dark0");
                Material.background: Theme.color("red");
                text: "Очистить кэш";
                onPressed: dialogwindow.open("Очистка кэша", "Вы уверены, что хотите очистить кэш радиолокационных изображений? \n" +
                                             "Все изображения, сохраненные на этом АРМ, будут удалены!", "warn", 3);
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
