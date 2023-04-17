import QtQuick 2.15
import Theme 1.0

import "../ui/buttons" as Buttons

Rectangle {
    property int i_CurrentTab: 0;

    color: Theme.color("dark1");
    Buttons.ClassicButton { id: btn_MapTab;
        property bool b_Active: i_CurrentTab === 0;

        anchors.left: parent.left;
        anchors.top: parent.top;

        fixed_width: 150;
        fixed_height: parent.height;
        label_text: "КАРТА";
        label_text_family: root.s_FontBold;
        background_color: b_Active ? Theme.color("dark2") : Theme.color("dark1");
        background_secondary_color: b_Active ? Theme.color("dark0") : Theme.color("dark3");
        label_color: Theme.color("light1");
        background_radius: 0;
        icon_source: "qrc:/icons/map.png";
        label_text_bold: true;
        label_text_size: 15;

        onClicked: i_CurrentTab = 0;
    }

    Buttons.ClassicButton { id: btn_FocusTab;
        property bool b_Active: i_CurrentTab === 1;

        anchors.left: btn_MapTab.right ;
        anchors.top: parent.top;

        fixed_width: 150;
        fixed_height: parent.height;
        label_text: "ФОКУСИРОВКА";
        label_text_family: root.s_FontBold;
        background_color: b_Active ? Theme.color("dark2") : Theme.color("dark1");
        background_secondary_color: b_Active ? Theme.color("dark0") : Theme.color("dark3");
        label_color: Theme.color("light1");
        background_radius: 0;
        icon_source: "qrc:/icons/crosshair.png";
        label_text_bold: true;
        label_text_size: 15;

        onClicked: i_CurrentTab = 1;
    }

    Buttons.ClassicButton { id: btn_SettingsTab;
        property bool b_Active: i_CurrentTab === 2;

        anchors.left: btn_FocusTab.right;
        anchors.top: parent.top;

        fixed_width: 150;
        fixed_height: parent.height;
        label_text: "НАСТРОЙКИ";
        label_text_family: root.s_FontBold;
        background_color: b_Active ? Theme.color("dark2") : Theme.color("dark1");
        background_secondary_color: b_Active ? Theme.color("dark0") : Theme.color("dark3");
        label_color: Theme.color("light1");
        background_radius: 0;
        icon_source: "qrc:/icons/settings.png";
        label_text_bold: true;
        label_text_size: 15;

        onClicked: i_CurrentTab = 2;
    }

    Buttons.ClassicButton { id: btn_InfoTab;
        property bool b_Active: i_CurrentTab === 3;

        anchors.left: btn_SettingsTab.right;
        anchors.top: parent.top;

        fixed_width: 150;
        fixed_height: parent.height;
        label_text: "О ПРОГРАММЕ";
        label_text_family: root.s_FontBold;
        background_color: b_Active ? Theme.color("dark2") : Theme.color("dark1");
        background_secondary_color: b_Active ? Theme.color("dark0") : Theme.color("dark3");
        label_color: Theme.color("light1");
        background_radius: 0;
        icon_source: "qrc:/icons/info.png";
        label_text_bold: true;
        label_text_size: 15;

        onClicked: i_CurrentTab = 3;
    }

    Buttons.ClassicButton { id: btn_ToggleConsole;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.rightMargin: 6;
        fixed_width: 24 ;
        fixed_height: 20;
        icon_px_size: 18;
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
