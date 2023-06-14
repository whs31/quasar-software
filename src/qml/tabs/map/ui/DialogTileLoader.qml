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
            onPressed: clr();
        }
    }
}
