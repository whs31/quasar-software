import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.15

import Theme 1.0
import Offline 1.0

Pane { id: dialog_TileLoader;
    property var poly: [];
    Material.elevation: 200;
    signal clr();

    property int tilezoom: 18;
    onTilezoomChanged: {
        if(poly.length > 2)
            tilecount = TileLoader.estimateTileCount(poly, tilezoom);
    }

    property int tilecount;
    onPolyChanged: {
        if(poly.length > 2)
            tilecount = TileLoader.estimateTileCount(poly, tilezoom);
    }

    Column {
        Row {
            RoundButton { id: button_Accept;
                enabled: poly.length >= 4;
                height: 44;
                radius: 4;
                font {
                    family: root.mainfont
                }
                text: "Загрузить выбранную область";

                icon.source: "qrc:/icons/google-material/take-photo.png";
                icon.color: enabled ? Theme.color("dark0") : Theme.color("light0");
                Material.background: enabled ? Theme.color("green") : Theme.color("dark2");
                Material.foreground: enabled ? Theme.color("dark0") : Theme.color("light0");
                Material.elevation: 30;
                onPressed: {
                    TileLoader.download(poly);
                    tilecount = 0;
                    clr();
                }
            }

            RoundButton { id: button_Clear;
                enabled: poly.length >= 1;
                height: 44;
                radius: 4;
                font {
                    family: root.mainfont
                }
                text: "Отмена";

                icon.source: "qrc:/icons/google-material/close.png";
                icon.color: enabled ? Theme.color("dark0") : Theme.color("light0");
                Material.background: enabled ? Theme.color("red") : Theme.color("dark2");
                Material.foreground: enabled ? Theme.color("dark0") : Theme.color("light0");
                Material.elevation: 30;
                onPressed: {
                    clr();
                    tilecount = 0;
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true;
            Layout.alignment: Qt.AlignRight;

            Slider { id: slider1;
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignLeft;
                from: 0;
                to: 18;
                value: 18;
                onValueChanged: tilezoom = value;
            }

            Text {
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignVCenter;
                font.family: root.mainfont;
                color: Theme.color("light0");
                font.pixelSize: 14;
                font.weight: Font.DemiBold;
                text: Number(slider1.value).toFixed(0) + " уровень";
                verticalAlignment: Text.AlignVCenter;
            }
        }

        Text {
            font {
                family: root.mainfont
                bold: true
                pixelSize: 15
            }
            text: "Ожидаемый размер загрузки: " + Number(tilecount * 16 / 1024).toFixed(0) + " МБ";
            color: Theme.color("light0");
        }
    }
}
