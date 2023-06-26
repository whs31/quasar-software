import QtQuick 2.15
import QtQuick.Controls 2.15
import Theme 1.0

Rectangle {
    property real latitude: 0;
    property real longitude: 0;

    height: 20;
    width: txt.paintedWidth + 10;
    color: ColorTheme.active.color(ColorTheme.BaseShade)

    Text { id: txt;
        property string s_LatSuffix: latitude > 0 ? "N" : "S";
        property string s_LonSuffix: longitude > 0 ? "E" : "W";

        anchors.centerIn: parent;
        font.family: root.mainfont;
        font.weight: Font.DemiBold;
        color: ColorTheme.active.color(ColorTheme.Text)
        textFormat: Text.RichText;
        text: "Широта: <b>" + Number(Math.abs(latitude)).toFixed(6) + "°" + s_LatSuffix +
              "</b>, долгота: <b>" + Number(Math.abs(longitude)).toFixed(6) + "°" + s_LonSuffix;
    }
}
