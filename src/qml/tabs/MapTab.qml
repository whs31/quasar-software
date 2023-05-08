import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtLocation 5.15
import QtPositioning 5.15

import Paths 1.0
import Theme 1.0
import RulerModel 1.0
import ClickHandler 1.0

import "map" as MapTab;

Map { id: c_Map;
    property int i_MapMode: 1; // { 0 - offline, 5 - schema, 4 - hybrid, 1 - sattelite }
    property bool b_ShowGrid: false;
    property bool b_ShowTrack: true;
    property bool b_ShowDiagram: true;
    property bool b_ShowCursorCoords: true;

    tilt: 15;
    gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.PinchGesture;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Paths.mapConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Paths.mapConfig());
    }

    activeMapType: c_Map.supportedMapTypes[i_MapMode];
    center: QtPositioning.coordinate(60, 30);
    zoomLevel: 5;
    copyrightsVisible: false;
    z: 0;
    Behavior on center { CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad; } }

    MouseArea { id: c_MapMouseArea;
        hoverEnabled: true;
        anchors.fill: parent;
        acceptedButtons: Qt.LeftButton | Qt.RightButton;

        onClicked: {
            if(ClickHandler.state === ClickHandler.RulerActive)
            {
                if(mouse.button === Qt.LeftButton)
                    c_RulerModel.insertPoint(c_Map.toCoordinate(Qt.point(mouseX, mouseY)), 0);
                if(mouse.button === Qt.RightButton)
                    c_RulerModel.resetRoute();
            }
        }
    }


    MapTab.UAV { id: c_UAV; }
    MapTab.UAVRoute { id: c_Route; }

    RulerModel { id: c_RulerModel; }
    MapTab.RulerItem { id: c_Ruler; fl_LastLatitude: c_RulerModel.lastLatitude; fl_LastLongitude: c_RulerModel.lastLongitude; }

    // ui

    Pane { id: panel_Tools;
        Material.elevation: 30;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.margins: 5;
        opacity: 0.85;

        Column {
            spacing: 15;

            Column {
                RoundButton { id: button_Ruler;
                    checkable: true;
                    checked: ClickHandler.state === ClickHandler.RulerActive;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/toolbar/map/ruler.png";
                    Material.elevation: 30;
                    onCheckedChanged: {
                        if(checked && ClickHandler.state === ClickHandler.Idle)
                            ClickHandler.state = ClickHandler.RulerActive;
                        else
                            ClickHandler.state = ClickHandler.Idle;
                    }
                }

                RoundButton { id: button_Protractor;
                    checkable: true;
                    checked: ClickHandler.state === ClickHandler.ProtractorActive;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/toolbar/map/protractor.png";
                    Material.elevation: 30;
                    onCheckedChanged: {
                        if(checked && ClickHandler.state === ClickHandler.Idle)
                            ClickHandler.state = ClickHandler.ProtractorActive;
                        else
                            ClickHandler.state = ClickHandler.Idle;
                    }
                }
            }

            Column {
                RoundButton { id: button_PanUAV;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/toolbar/map/gps.png";
                    Material.elevation: 30;
                    onPressed: c_Map.center = c_UAV.coordinate;
                }

                RoundButton { id: button_PanLastImage;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/toolbar/map/map.png";
                    Material.elevation: 30;
                    //onPressed: c_Map.center = c_UAV.coordinate;
                }
            }
        }
    }

    Pane { id: panel_Entities;
        anchors.top: panel_Tools.bottom;
        anchors.topMargin: 30;
        anchors.left: parent.left;
        anchors.margins: 5;
        opacity: 0.85;

        Column {
            RoundButton { id: button_Marker;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/toolbar/map/marker.png";
                Material.elevation: 30;
                //onPressed:
            }

            RoundButton { id: button_PlannerPoint;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/toolbar/map/pin.png";
                Material.elevation: 30;
                //onPressed:
            }
        }
    }

    Pane { id: panel_Parameters;
        property bool b_Expanded: false;

        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.margins: 5;
        opacity: 0.85;
        width: b_Expanded ? implicitWidth : 0;
        height: b_Expanded ? implicitHeight : 0;
        visible: height > 0;
        Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; } }
        Behavior on width { NumberAnimation { easing.type: Easing.InOutQuad; } }
        clip: true;

        Column {
            spacing: -5;

            CheckBox { id: checkbox_FollowUAV;
                font.family: root.s_FontMain;
                checked: false;
                text: "Следить за БПЛА";
                //onCheckedChanged: binding)
            }

            CheckBox { id: checkbox_EnableGrid;
                font.family: root.s_FontMain;
                checked: false;
                text: "Отображать масштабную сетку";
                //onCheckedChanged:
            }

            CheckBox { id: checkbox_ShowCursorCoords;
                font.family: root.s_FontMain;
                checked: true;
                text: "Отображать координаты курсора";
                //onCheckedChanged:
            }

            CheckBox { id: checkbox_ShowTrack;
                font.family: root.s_FontMain;
                checked: true;
                text: "Отображать трек полёта";
                //onCheckedChanged:
            }

            CheckBox { id: checkbox_ShowDiagram;
                font.family: root.s_FontMain;
                checked: true;
                text: "Отображать диаграмму направленности";
                //onCheckedChanged:
            }

            RoundButton { id: button_ClearTrack;
                radius: 4;
                icon.source: "qrc:/icons/toolbar/map/eraser.png";
                height: 44;
                font.family: root.s_FontMain;
                width: checkbox_ShowDiagram.width;
                text: "Очистить трек полёта";
                Material.background: Theme.color("red");
                //onPressed:
            }
        }
    }

    RoundButton { id: button_ExpandParameters;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.margins: 5;
        checkable: true;
        height: 40;
        width: 40;
        radius: 4;
        icon.source: "qrc:/icons/toolbar/map/expand.png";
        Material.elevation: 30;
        Material.background: Material.background;
        Material.primary: Material.primary;
        Material.accent: Material.accent;
        onCheckedChanged: panel_Parameters.b_Expanded = checked;
    }

    Row { id: layout_ImageTools;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.margins: 5;

        RoundButton { id: button_FetchImages;
            font.family: root.s_FontMain;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/toolbar/map/refresh.png";
            Material.elevation: 30;
            Material.background: Material.background;
            //onPressed:
        }

        RoundButton { id: button_ChooseCatalogue;
            font.family: root.s_FontMain;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/toolbar/map/folder.png";
            Material.elevation: 30;
            Material.background: Material.background;
            text: "Изменить каталог РЛИ";
            //onPressed:
        }

        RoundButton { id: button_ClearLocalCache;
            font.family: root.s_FontMain;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/toolbar/map/trash.png";
            Material.elevation: 30;
            Material.background: Material.background;
            text: "Очистить кэш";
            //onPressed:
        }
    }

    Row { id: layout_MapMode;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.margins: 5;

        ComboBox { id: control_MapMode;
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            width: 170;
            currentIndex: 2;
            model: ["Оффлайн-карта", "Схема", "Спутник", "Гибрид"];

            onCurrentValueChanged: {
                if(currentValue === "Оффлайн-карта")
                    i_MapMode = 0;
                if(currentValue === "Схема")
                    i_MapMode = 5;
                if(currentValue === "Спутник")
                    i_MapMode = 1;
                if(currentValue === "Гибрид")
                    i_MapMode = 4;
            }
        }
    }
}
