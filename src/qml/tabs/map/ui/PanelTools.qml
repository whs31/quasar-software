import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import ClickHandler 1.0
import Images 1.0

import "../../../widgets" as Widgets

Pane {
    Material.elevation: 30;

    function panImage()
    {
        button_PanLastImage.self();
    }

    Column {
        spacing: 15;

        Column {
            RoundButton { id: button_Ruler;
                checkable: true;
                checked: ClickHandler.state === ClickHandler.RulerActive;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/vector/toolbar/ruler.svg";
                icon.color: checked ? theme.base : theme.text
                Material.elevation: 30;
                Material.background: checked ? theme.yellow : theme.surface0
                onCheckedChanged: {
                    if(checked && ClickHandler.state === ClickHandler.Idle)
                        ClickHandler.state = ClickHandler.RulerActive;
                    else
                        ClickHandler.state = ClickHandler.Idle;
                }

                Widgets.TT { txt: "Инструмент линейки"; }
            }

            RoundButton { id: button_TileLoader;
                checkable: true;
                checked: ClickHandler.state === ClickHandler.TileLoaderActive;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/vector/toolbar/select.svg";
                icon.color: checked ? theme.base : theme.text
                Material.elevation: 30;
                Material.background: checked ? theme.green : theme.surface0
                onCheckedChanged: {
                    if(checked && ClickHandler.state === ClickHandler.Idle)
                        ClickHandler.state = ClickHandler.TileLoaderActive;
                    else
                        ClickHandler.state = ClickHandler.Idle;
                }

                Widgets.TT { txt: "Инструмент загрузки оффлайн-карт"; }
            }
        }

        Column {
            RoundButton { id: button_PanUAV;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/vector/toolbar/gps.svg";
                icon.color: theme.text
                Material.elevation: 30;
                Material.background: theme.surface0
                onPressed: maptab_root.center = c_UAV.coordinate;

                Widgets.TT { txt: "Центрировать карту на БПЛА"; }
            }

            RoundButton { id: button_PanLastImage;
                function self() {
                    console.log("[GUI] Panned at " + ImagesModel.lastImagePosition());
                    maptab_root.center = ImagesModel.lastImagePosition();
                }

                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/vector/toolbar/image_search.svg";
                icon.color: theme.text
                Material.background: theme.surface0
                Material.elevation: 30;
                onPressed: self();

                Widgets.TT { txt: "Центрировать карту на последнем полученном изображении"; }
            }
        }
    }
}
