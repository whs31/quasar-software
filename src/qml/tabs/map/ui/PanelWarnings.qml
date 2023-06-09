import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Notifications 1.0

ListView {
    add: Transition { NumberAnimation { properties: "x,y"; duration: 1000; } }
    model: WarningsModel;
    delegate: RowLayout {
        RoundButton {
            flat: true;
            icon.source: "qrc:/icons/google-material/warning.png";
            icon.color: major ? Theme.color("red")
                              : Theme.color("orange");
        }

        Text {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            font {
                family: root.mainfont
                pixelSize: 18
                weight: Font.ExtraBold
                capitalization: Font.AllUppercase
            }

            text: message;
            color: major ? Theme.color("red")
                         : Theme.color("orange");
            verticalAlignment: Text.AlignVCenter;
        }

    }

    height: 300;
}
