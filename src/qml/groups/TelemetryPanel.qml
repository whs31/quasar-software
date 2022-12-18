import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI

UI.RoundPane {
    id: base;
    radius: 20;
    Material.elevation: 20;
    property string textLatitude: "0.0000000";
    property string textLongitude: "0.0000000";
    property string textSpeed: "0";
    property string textElevation: "0.0";
    //sats also here?

    GridLayout {
        columns: 2;
        columnSpacing: 10;
        Text {
            id: latitudeText;
            color: "#dae1e5";
            font.bold: true
            textFormat: Text.RichText
            text: textLatitude + "°";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            Layout.alignment: Qt.AlignCenter;
        }
        Text {
            id: longitudeText;
            color: "#dae1e5";
            font.bold: true
            textFormat: Text.RichText
            text: textLongitude + "°";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            Layout.alignment: Qt.AlignCenter;
        }
        Text {
            id: speedText;
            color: "#dae1e5";
            font.bold: true
            textFormat: Text.RichText
            text: textSpeed + " <i>км/ч</i>";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            Layout.alignment: Qt.AlignCenter;
        }
        Text {
            id: elevationText;
            color: "#dae1e5";
            font.bold: true
            textFormat: Text.RichText
            text: textElevation + " <i>м</i>";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            Layout.alignment: Qt.AlignCenter;
        }
    }
}
