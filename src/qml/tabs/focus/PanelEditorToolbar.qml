import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0

Pane { id: panel_EditorToolbar;
    Material.elevation: 30;

    Row {
        RoundButton { id: button_FormImage;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/refresh.png";
            icon.color: Theme.color("dark0");
            text: "Переформирование изображения";
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("orange");
            onPressed: Network.executeCommand(Network.ReformImage);
        }

        RoundButton { id: button_FocusImage;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/take-photo.png";
            icon.color: Theme.color("dark0");
            text: "Фокусировка изображения";
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("accent");
            onPressed: Network.executeCommand(Network.FocusImage);
        }
    }
}
