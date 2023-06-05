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

            ScrollView {id: layout_Meta;
                Layout.fillWidth: true;
                visible: button_ImageParams.checked;
                implicitHeight: 300;
                implicitWidth: parent.width;
                clip: true;
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn;

                GridLayout {
                    columns: 2;
                    columnSpacing: 6;
                    rowSpacing: 4;

                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
                    Rectangle { width: 100; height: 100; color: "red"; }
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
