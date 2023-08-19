import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Pane {
    property real latitude: 0
    property real longitude: 0
    property string private_LatSuffix: latitude > 0 ? "N" : "S"
    property string private_LonSuffix: longitude > 0 ? "E" : "W"

    RowLayout {
        Text {
            color: theme.subtext0
            font {
                family: root.mainfont
                weight: Font.DemiBold
                pixelSize: 13
            }

            text: "Широта:"
        }

        Text {
            Layout.preferredWidth: 85
            color: theme.text
            text: Number(Math.abs(latitude)).toFixed(6) + "°" + private_LatSuffix

            font {
                family: root.mainfont
                pixelSize: 13
                weight: Font.ExtraBold
            }
        }

        Text {
            color: theme.subtext0
            text: "Долгота:"

            font {
                family: root.mainfont
                pixelSize: 13
                weight: Font.DemiBold
            }
        }
        Text {
            Layout.preferredWidth: 85
            color: theme.text
            text: Number(Math.abs(longitude)).toFixed(6) + "°" + private_LonSuffix

            font {
                family: root.mainfont
                pixelSize: 13
                weight: Font.ExtraBold
            }
        }
    }
}
