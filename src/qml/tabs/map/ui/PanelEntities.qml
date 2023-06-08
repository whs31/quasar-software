import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import ClickHandler 1.0
import Images 1.0
import Markers 1.0

Pane { id: panel_Entities;
    Material.elevation: 30;

    Column {
        RoundButton { id: button_Marker;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/marker.png";
            icon.color: ClickHandler.state === ClickHandler.MarkerActive ? Theme.color("dark0") : Theme.color("light0");
            Material.elevation: 30;
            Material.background: ClickHandler.state === ClickHandler.MarkerActive ? Theme.color("accent") : Theme.color("dark2");
            onPressed: ClickHandler.state = ClickHandler.MarkerActive;

            ToolTip { id: tt1;
                visible: parent.hovered;
                font {
                    family: root.mainfont
                    pixelSize: 13
                }

                contentItem: Text {
                    text: tt1.text
                    font: tt1.font
                    color: Theme.color("dark0");
                }

                background: Rectangle {
                    color: Theme.color("light1");
                    radius: 3;
                }

                delay: 500;
                text: "Установка нового маркера карты";
            }
        }

        RoundButton { id: button_PlannerPoint;
            enabled: false;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/flag.png";
            icon.color: Theme.color("light0");
            Material.background: ClickHandler.state === ClickHandler.PlannerActive ? Theme.color("accent") : Theme.color("dark2");
            Material.elevation: 30;
            onPressed: ClickHandler.state = ClickHandler.PlannerActive;

            ToolTip { id: tt2;
                visible: parent.hovered;
                font {
                    family: root.mainfont
                    pixelSize: 13
                }

                contentItem: Text {
                    text: tt2.text
                    font: tt2.font
                    color: Theme.color("dark0");
                }

                background: Rectangle {
                    color: Theme.color("light1");
                    radius: 3;
                }

                delay: 500;
                text: "Установка новой точки планировщика заданий";
            }
        }

        RoundButton { id: button_ClearMarkers;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/remove-layer.png";
            icon.color: Theme.color("light0");
            Material.background: Theme.color("dark2");
            Material.elevation: 30;
            onPressed: dialogwindow.open("Удаление маркеров", "Вы уверены, что хотите удалить все маркеры карты?", "warn", 2);

            ToolTip { id: tt3;
                visible: parent.hovered;
                font {
                    family: root.mainfont
                    pixelSize: 13
                }

                contentItem: Text {
                    text: tt3.text
                    font: tt3.font
                    color: Theme.color("dark0");
                }

                background: Rectangle {
                    color: Theme.color("light1");
                    radius: 3;
                }

                delay: 500;
                text: "Очистка карты от маркеров и точек ПЗ";
            }

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 2 && status === true) {
                        console.log("[GUI] Markers cleared");
                        MarkersModel.clear();
                    }
                }
            }
        }

        RoundButton { id: button_ClearImages;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/remove-image.png";
            icon.color: Theme.color("light0");
            Material.background: Theme.color("dark2");
            Material.elevation: 30;
            onPressed: dialogwindow.open("Удаление РЛИ", "Вы уверены, что хотите удалить все радиолокационные изображения с карты?", "warn", 4);

            ToolTip { id: tt4;
                visible: parent.hovered;
                font {
                    family: root.mainfont
                    pixelSize: 13
                }

                contentItem: Text {
                    text: tt4.text
                    font: tt4.font
                    color: Theme.color("dark0");
                }

                background: Rectangle {
                    color: Theme.color("light1");
                    radius: 3;
                }

                delay: 500;
                text: "Очистка карты от изображений";
            }

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 4 && status === true) {
                        console.log("[GUI] Images cleared");
                        ImagesModel.clear();
                    }
                }
            }
        }

        RoundButton { id: button_ToggleImages;
            enabled: false;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/hide.png";
            icon.color: Theme.color("light0");
            Material.background: Theme.color("dark2");
            Material.elevation: 30;

            ToolTip { id: tt5; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                      contentItem: Text { text: tt5.text; font: tt5.font;  color: Theme.color("dark0"); }
                      background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                      text: "Переключение видимости изображений"; }

//                onPressed: {

//                }
        }
    }
}
