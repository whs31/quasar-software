import QtQuick 2.15
import Theme 1.0

import "bottombar" as Bottom
import "../ui/buttons" as Buttons

Rectangle {
    color: Theme.color("dark1");

    Bottom.StatusWidget { id: c_StatusWidget;
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top: parent.top;
    }

    Bottom.InfoPanel { id: c_InfoPanel;
        anchors.left: c_StatusWidget.right;
        anchors.leftMargin: 16;
        anchors.top: parent.top;
    }

    Buttons.ClassicButton { id: btn_ToggleConsole;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.margins: 6;
        fixed_width: 24;
        fixed_height: 22;
        label_color: Theme.color("light1");
        icon_px_size: 19;
        icon_source: "qrc:/icons/bottombar/console.png";
        background_radius: 0;
        background_color: Theme.color("dark2");
        background_secondary_color: Qt.lighter(background_color, 1.5);
        tooltip_text: "Консоль отладки";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.b_ConsoleShown = !root.b_ConsoleShown;
        }
    }
}
