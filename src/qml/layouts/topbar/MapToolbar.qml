import QtQuick 2.15
import Theme 1.0

import "../../ui/checkboxes" as Checkboxes

Item {
    Checkboxes.LightCheckbox { id: checkbox_UseOnlineMaps;
        property int i_LastUsedMapMode: 1;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.leftMargin: 8;
        anchors.topMargin: 8;

        fixed_width: 140;
        fixed_height: 16;
        label_text: "ОНЛАЙН-КАРТА";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color3");
        checked: true;

        onCheckedChanged: {
            if(checked)
                root.i_CurrentMapMode = i_LastUsedMapMode;
            else
            {
                root.i_CurrentMapMode = 0;
            }
        }
    }

    Text { id: label_MapMode;
        text: "РЕЖИМ КАРТЫ";
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        anchors.top: checkbox_UseOnlineMaps.bottom;
        anchors.topMargin: 3;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        width: 123;
        height: 12;
        color: Theme.color("light1");

        enabled: checkbox_UseOnlineMaps.checked;
    }

    Image { id: button_MapModeSchema;
        anchors.top: label_MapMode.bottom;
        anchors.topMargin: 6;
        anchors.left: label_MapMode.left;
        source: checkbox_UseOnlineMaps.i_LastUsedMapMode === 5 && checkbox_UseOnlineMaps.checked ? "qrc:/icons/toolbar/map/schema-active.png"
                                                               : "qrc:/icons/toolbar/map/schema-disabled.png";
        width: 50;
        height: 18;

        enabled: checkbox_UseOnlineMaps.checked;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                checkbox_UseOnlineMaps.i_LastUsedMapMode = 5;
                root.i_CurrentMapMode = 5;
            }
        }
    }

    Image { id: button_MapModeSat;
        anchors.top: button_MapModeSchema.top;
        anchors.left: button_MapModeSchema.right;
        anchors.leftMargin: 2;
        source: checkbox_UseOnlineMaps.i_LastUsedMapMode === 1 && checkbox_UseOnlineMaps.checked ? "qrc:/icons/toolbar/map/sat-active.png"
                                                               : "qrc:/icons/toolbar/map/sat-disabled.png";
        width: 50;
        height: 18;

        enabled: checkbox_UseOnlineMaps.checked;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                checkbox_UseOnlineMaps.i_LastUsedMapMode = 1;
                root.i_CurrentMapMode = 1;
            }
        }
    }

    Image { id: button_MapModeHybrid;
        anchors.top: button_MapModeSat.top;
        anchors.left: button_MapModeSat.right;
        anchors.leftMargin: 2;
        source: checkbox_UseOnlineMaps.i_LastUsedMapMode === 4 && checkbox_UseOnlineMaps.checked ? "qrc:/icons/toolbar/map/hybrid-active.png"
                                                               : "qrc:/icons/toolbar/map/hybrid-disabled.png";
        width: 50;
        height: 18;

        enabled: checkbox_UseOnlineMaps.checked;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                checkbox_UseOnlineMaps.i_LastUsedMapMode = 4;
                root.i_CurrentMapMode = 4;
            }
        }
    }
}
