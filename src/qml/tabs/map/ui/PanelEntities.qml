import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import ClickHandler 1.0
import Images 1.0
import Markers 1.0

import "../../../widgets" as Widgets

Pane { id: panel_Entities;
    Material.elevation: 30;

    Column {
        RoundButton { id: button_Marker;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/toolbar/marker_new.svg";
            icon.color: ClickHandler.state === ClickHandler.MarkerActive ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.background: ClickHandler.state === ClickHandler.MarkerActive ? ColorTheme.active.color(ColorTheme.Accent) : ColorTheme.active.color(ColorTheme.Surface);
            onPressed: ClickHandler.state = ClickHandler.MarkerActive;

            Widgets.TT { txt: "Установка нового маркера карты"; }
        }

        RoundButton { id: button_PlannerPoint;
            enabled: false;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/toolbar/bookmark_new.svg";
            icon.color: ColorTheme.active.color(ColorTheme.Text);
            Material.background: ClickHandler.state === ClickHandler.PlannerActive ? ColorTheme.active.color(ColorTheme.Accent) : ColorTheme.active.color(ColorTheme.Surface);
            Material.elevation: 30;
            onPressed: ClickHandler.state = ClickHandler.PlannerActive;

            Widgets.TT { txt: "Установка новой точки полётного задания"; }
        }

        RoundButton { id: button_ClearMarkers;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/toolbar/marker_remove.svg";
            icon.color: ColorTheme.active.color(ColorTheme.Text);
            Material.background: ColorTheme.active.color(ColorTheme.Surface);
            Material.elevation: 30;
            onPressed: dialogwindow.open("Удаление маркеров", "Вы уверены, что хотите удалить все маркеры карты?", "warn", 2);

            Widgets.TT { txt: "Очистить карту от маркеров и точек полётного задания"; }

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
            icon.source: "qrc:/icons/vector/toolbar/photo_remove.svg";
            icon.color: ColorTheme.active.color(ColorTheme.Text);
            Material.background: ColorTheme.active.color(ColorTheme.Surface);
            Material.elevation: 30;
            onPressed: dialogwindow.open("Удаление РЛИ", "Вы уверены, что хотите удалить все радиолокационные изображения с карты?", "warn", 4);

            Widgets.TT { txt: "Очистить карту от радиолокационных изображений"; }

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 4 && status === true) {
                        console.log("[GUI] Images cleared");
                        ImagesModel.clear();
                        StreamSegmentModel.clear();
                    }
                }
            }
        }

        RoundButton { id: button_StripEraser;
            enabled: false;
            visible: false;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/toolbar/eraser.svg";
            icon.color: ClickHandler.state === ClickHandler.EraserActive ? ColorTheme.active.color(ColorTheme.Dark)
                                                                         : ColorTheme.active.color(ColorTheme.Text)
            Material.background: ClickHandler.state === ClickHandler.EraserActive ? ColorTheme.active.color(ColorTheme.Red)
                                                                                  : ColorTheme.active.color(ColorTheme.Surface);
            Material.elevation: 30;
            onPressed: {
                if(ClickHandler.state === ClickHandler.EraserActive)
                    ClickHandler.state = ClickHandler.Idle
                else
                    ClickHandler.state = ClickHandler.EraserActive
            }

            Widgets.TT { txt: "Инструмент очистки карты от потоковых РЛИ"; }
        }
    }
}
