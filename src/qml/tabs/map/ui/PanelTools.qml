import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import ClickHandler 1.0
import Images 1.0

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
                icon.source: "qrc:/icons/google-material/ruler.png";
                icon.color: checked ? Theme.color("dark0") : Theme.color("light0");
                Material.elevation: 30;
                Material.background: checked ? Theme.color("yellow") : Theme.color("dark2");
                onCheckedChanged: {
                    if(checked && ClickHandler.state === ClickHandler.Idle)
                        ClickHandler.state = ClickHandler.RulerActive;
                    else
                        ClickHandler.state = ClickHandler.Idle;
                }

                ToolTip { id: tt1; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt1.text; font: tt1.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Инструмент линейки"; }
            }

            RoundButton { id: button_Protractor;
                enabled: false;
                checkable: true;
                checked: ClickHandler.state === ClickHandler.ProtractorActive;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/ruler2.png";
                icon.color: checked ? Theme.color("dark0") : Theme.color("light0");
                Material.elevation: 30;
                Material.background: checked ? Theme.color("accent") : Theme.color("dark2");
                onCheckedChanged: {
                    if(checked && ClickHandler.state === ClickHandler.Idle)
                        ClickHandler.state = ClickHandler.ProtractorActive;
                    else
                        ClickHandler.state = ClickHandler.Idle;
                }

                ToolTip { id: tt2; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt2.text; font: tt2.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Инструмент для измерения углов"; }
            }
        }

        Column {
            RoundButton { id: button_PanUAV;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/gps.png";
                icon.color: Theme.color("light0");
                Material.elevation: 30;
                Material.background: Theme.color("dark2");
                onPressed: maptab_root.center = c_UAV.coordinate;

                ToolTip { id: tt3; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt3.text; font: tt3.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Центрировать карту на БПЛА"; }
            }

            RoundButton { id: button_PanLastImage;
                function self() {
                    console.log("[GUI] Panned at " + ImagesModel.lastImagePosition());
                    maptab_root.center = ImagesModel.lastImagePosition();
                }

                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/image-gps.png";
                icon.color: Theme.color("light0");
                Material.background: Theme.color("dark2");
                Material.elevation: 30;
                onPressed: self();

                ToolTip { id: tt4; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt4.text; font: tt4.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Центрировать карту на последнем полученном изображении"; }
            }
        }
    }
}
