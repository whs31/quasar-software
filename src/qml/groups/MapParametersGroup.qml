import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

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
            
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 0;
            
            onCheckedChanged: {
                RuntimeData.followPlane = checked;
            }
            contentItem: Rectangle {
                Image {
                    id: ico;
                    width: 16;
                    height: 16;
                    source: "qrc:/ui-resources/white/plane.png";
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    smooth: true;
                }
                Text {
                    text: "Следить за бортом";
                    font.capitalization: Font.MixedCase; 
                    font.pixelSize: 11;
                    color: "#dae1e5";
                    opacity: enabled ? 1.0 : 0.3
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: ico.right;
                    anchors.leftMargin: 3;
                }
            }
        }
        CheckBox {
            id: checkboxDrawTooltip;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            anchors.left: parent.left;
            anchors.top: checkboxFollowPlane.bottom;
            anchors.topMargin: -20;
            onCheckedChanged: {
                RuntimeData.drawTooltip = checked;
            }
            contentItem: Rectangle {
                Image {
                    id: ico0;
                    width: 16;
                    height: 16;
                    source: "qrc:/ui-resources/white/eyedropper.png";
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    smooth: true;
                }
                Text {
                    text: "Координаты курсора";
                    font.capitalization: Font.MixedCase; 
                    font.pixelSize: 11;
                    color: "#dae1e5";
                    opacity: enabled ? 1.0 : 0.3
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: ico0.right;
                    anchors.leftMargin: 3;
                }
            }
        }

        CheckBox {
            id: checkboxDrawRoute;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            anchors.left: parent.left;
            anchors.top: checkboxDrawTooltip.bottom;
            anchors.topMargin: -10;
            onCheckedChanged: {
                RuntimeData.drawRoute = checked;
            }
            contentItem: Rectangle {
                Image {
                    id: ico1;
                    width: 16;
                    height: 16;
                    source: "qrc:/ui-resources/white/route.png";
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    smooth: true;
                }
                Text {
                    text: "Траектория полёта";
                    font.capitalization: Font.MixedCase; 
                    font.pixelSize: 11;
                    color: "#dae1e5";
                    opacity: enabled ? 1.0 : 0.3
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: ico1.right;
                    anchors.leftMargin: 3;
                }
            }
        }
        CheckBox {
            id: checkboxDrawPredict;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            anchors.left: parent.left;
            anchors.top: checkboxDrawRoute.bottom;
            anchors.topMargin: -20;
            onCheckedChanged: {
                RuntimeData.drawPredict = checked;
            }
            contentItem: Rectangle {
                Image {
                    id: ico2;
                    width: 16;
                    height: 16;
                    source: "qrc:/ui-resources/white/curve.png";
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    smooth: true;
                }
                Text {
                    text: "Направление полёта";
                    font.capitalization: Font.MixedCase; 
                    font.pixelSize: 11;
                    color: "#dae1e5";
                    opacity: enabled ? 1.0 : 0.3
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: ico2.right;
                    anchors.leftMargin: 3;
                }
            }
        }
        CheckBox {
            id: checkboxDrawDiagram;
            checked: true;
            indicator.implicitWidth: 14;
            indicator.implicitHeight: 14;
            anchors.left: parent.left;
            anchors.top: checkboxDrawPredict.bottom;
            anchors.topMargin: -20;
            onCheckedChanged: {
                RuntimeData.drawDiagram = checked;
            }
            contentItem: Rectangle {
                Image {
                    id: ico3;
                    width: 14;
                    height: 14;
                    source: "qrc:/ui-resources/white/radar.png";
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    smooth: true;
                }
                Text {
                    text: "Диаграмма направленности";
                    font.capitalization: Font.MixedCase; 
                    font.pixelSize: 11;
                    color: "#dae1e5";
                    opacity: enabled ? 1.0 : 0.3
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: ico3.right;
                    anchors.leftMargin: 3;
                }
            }
        }
    }
}
