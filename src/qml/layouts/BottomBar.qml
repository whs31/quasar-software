import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

import "bottombar" as Bottom

Rectangle {
    color: Theme.color("dark1");

    Bottom.StatusWidget { id: c_StatusWidget;
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top: parent.top;
    }

    Flickable {
        anchors.left: c_StatusWidget.right;
        anchors.leftMargin: 16;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: layout_SharedToolbar.left;
        clip: true;
        interactive: true;
        contentWidth: c_InfoPanel.width;
        flickableDirection: Flickable.HorizontalFlick;

        Bottom.InfoPanel { id: c_InfoPanel; }
    }

    Row { id: layout_SharedToolbar;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        RoundButton { id: button_Settings;
            font.family: root.mainfont;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/tabs/settings.png";
            Material.elevation: 30;
            onPressed: {
                if(c_SettingsWindow.visible === true)
                    c_SettingsWindow.hide();
                else
                    c_SettingsWindow.show();
            }
        }

        RoundButton { id: button_About;
            font.family: root.mainfont;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/tabs/info.png";
            Material.elevation: 30;
            onPressed: {
                if(c_InfoWindow.b_Shown)
                    c_InfoWindow.b_Shown = false;
                else
                    c_InfoWindow.b_Shown = true;
            }
        }

        RoundButton { id: button_ToggleDebug;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/bottombar/console.png";
            onPressed: root.b_ConsoleShown = !root.b_ConsoleShown;
        }
    }
}
