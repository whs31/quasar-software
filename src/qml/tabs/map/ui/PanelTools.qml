import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import ClickHandler 1.0
import Images 1.0

Pane {
    Material.elevation: 30;

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
                onPressed: c_Map.center = c_UAV.coordinate;
            }

            RoundButton { id: button_PanLastImage;
                function self() {
                    console.log("[GUI] Panned at " + ImagesModel.lastImagePosition());
                    c_Map.center = ImagesModel.lastImagePosition();
                }

                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/image-gps.png";
                icon.color: Theme.color("light0");
                Material.background: Theme.color("dark2");
                Material.elevation: 30;
                onPressed: self();
            }
        }
    }
}
