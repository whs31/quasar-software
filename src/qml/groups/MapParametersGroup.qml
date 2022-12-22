import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Rectangle 
{
    property int containerHeight: 170;
    
    RoundButton
    {
        id: expandButton;
        icon.source: "qrc:/ui-resources/white/earth.png";
        icon.color: "#dae1e5";
        Material.background: "#204040"
        icon.width: 12;
        icon.height: 24;
        height: 32;
        radius: 32;
        opacity: 1;
        text: "Параметры интерактивной карты";
        font.capitalization: Font.MixedCase; 
        font.pixelSize: 11;
        onClicked: box.shown = !box.shown;
        z: 100;
    }

    UI.RoundPane {
        id: box;
        anchors.top: expandButton.top;
        anchors.topMargin: 10;
        anchors.left: expandButton.left;
        anchors.leftMargin: 5;
        anchors.right: expandButton.right;
        anchors.rightMargin: 5;
        opacity: 0.75;
        z: 99;

        //collapsible panel
        property bool shown: false;
        visible: height > 0;
        height: shown ? containerHeight : 0;
        Behavior on height {
            NumberAnimation {
                easing.type: Easing.InOutQuad;
            }
        }
        clip: true

        UI.CustomCheckbox {
            id: checkboxFollowPlane;
            checked: false;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 15;
            iconsource: "qrc:/ui-resources/white/plane.png";
            labeltext: "Следить за бортом";

            onCheckedChanged: { RuntimeData.followPlane = checked; }
        }
        UI.CustomCheckbox {
            id: checkboxDrawTooltip;
            checked: true;
            anchors.left: parent.left;
            anchors.top: checkboxFollowPlane.bottom;
            anchors.topMargin: 10;
            iconsource: "qrc:/ui-resources/white/eyedropper.png";
            labeltext: "Координаты курсора";

            onCheckedChanged: { RuntimeData.drawTooltip = checked; }
        }
        UI.CustomCheckbox {
            id: checkboxDrawRoute;
            checked: true;
            anchors.left: parent.left;
            anchors.top: checkboxDrawTooltip.bottom;
            anchors.topMargin: 20;
            iconsource: "qrc:/ui-resources/white/route.png";
            labeltext: "Траектория полёта";

            onCheckedChanged: { RuntimeData.drawRoute = checked; }
        }
        UI.CustomCheckbox {
            id: checkboxDrawPredict;
            checked: true;
            anchors.left: parent.left;
            anchors.top: checkboxDrawRoute.bottom;
            anchors.topMargin: 10;
            iconsource: "qrc:/ui-resources/white/curve.png";
            labeltext: "Направление полёта";

            onCheckedChanged: { RuntimeData.drawPredict = checked; }
        }
        UI.CustomCheckbox {
            id: checkboxDrawDiagram;
            checked: true;
            anchors.left: parent.left;
            anchors.top: checkboxDrawPredict.bottom;
            anchors.topMargin: 10;
            iconsource: "qrc:/ui-resources/white/radar.png";
            labeltext: "Диаграмма направленности";

            onCheckedChanged: { RuntimeData.drawDiagram = checked; }
        }
    }
}
