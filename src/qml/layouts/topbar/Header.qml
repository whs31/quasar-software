import QtQuick 2.15
import Theme 1.0

import "../../ui/buttons" as Buttons;

Item {
    Buttons.ClassicButton { id: btn_QuitButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        anchors.right: parent.right;
        anchors.rightMargin: 6;
        fixed_width: 47;
        fixed_height: 27;
        icon_px_size: 15;
        icon_source: "qrc:/icons/close.png";
        background_color: Theme.color("red");
        background_secondary_color: Qt.lighter(background_color, 1.5);
        background_radius: 2;
        tooltip_text: "Выход на рабочий стол";
        tooltip_enabled: true;
        label_text_family: root.s_FontSemiBold;
        onClicked: {
            Qt.quit();
        }
    }

    Buttons.ClassicButton { id: btn_MinimizeButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: btn_QuitButton.top;
        anchors.right: btn_QuitButton.left;
        anchors.rightMargin: 6;
        fixed_width: 47;
        fixed_height: 27;
        icon_px_size: 15;
        icon_source: "qrc:/icons/minus.png";
        background_color: Theme.color("dark2");
        background_secondary_color: Qt.lighter(background_color, 1.5);
        background_radius: 2;
        tooltip_text: "Свернуть окно";
        tooltip_enabled: true;
        label_text_family: root.s_FontSemiBold;
        onClicked: {
            root.showMinimized();
        }
    }

    Buttons.ClassicButton { id: btn_ToggleConsole;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: btn_QuitButton.top;
        anchors.right: btn_MinimizeButton.left;
        anchors.rightMargin: 6;
        fixed_width: 27;
        fixed_height: 27;
        icon_px_size: 20;
        icon_source: "qrc:/icons/command-line.png";
        background_color: Theme.color("dark2");
        background_secondary_color: Qt.lighter(background_color, 1.5);
        background_radius: 2;
        tooltip_text: "Консоль отладки";
        tooltip_enabled: true;
        label_text_family: root.s_FontSemiBold;
        onClicked: {
            root.b_ConsoleShown = !root.b_ConsoleShown;
        }
    }
}
