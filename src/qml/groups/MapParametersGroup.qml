import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import DiskManager 1.0

Rectangle 
{
    property int containerHeight: 160;
    
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
        text: "Настройки интерактивной карты";
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

        CheckBox {
            id: checkboxFollowPlane;
            checked: false;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            text: "Следить за бортом";
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 0;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
        }
        CheckBox {
            id: checkboxDrawTooltip;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            text: "Координаты курсора";
            anchors.left: parent.left;
            anchors.top: checkboxFollowPlane.bottom;
            anchors.topMargin: -20;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
        }

        CheckBox {
            id: checkboxDrawRoute;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            text: "Траектория полёта";
            anchors.left: parent.left;
            anchors.top: checkboxDrawTooltip.bottom;
            anchors.topMargin: -10;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
        }
        CheckBox {
            id: checkboxDrawPredict;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            text: "Направление полёта";
            anchors.left: parent.left;
            anchors.top: checkboxDrawRoute.bottom;
            anchors.topMargin: -20;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
        }
        CheckBox {
            id: checkboxDrawDiagram;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            text: "Диаграмма направленности";
            anchors.left: parent.left;
            anchors.top: checkboxDrawPredict.bottom;
            anchors.topMargin: -20;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
        }
    }
}
