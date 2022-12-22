import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property int iconsize: 16;
    property string iconsource: "qrc:/ui-resources/white/close.png";
    
    property string labeltext: "Not assigned";
    property color textcolor: "#dae1e5";
    property color primarycolor: "#204040";
    property color accentcolor: "#43a1ca";

    property bool checked: false;

    width: checkboxIndicator.width + iconsize + 150 + 3;
    height: childrenRect.height;
    
    id: control;
            
    Rectangle {
        id: checkboxIndicator;
        color: primarycolor;
        anchors.left: parent.left;
        implicitWidth: 16;
        implicitHeight: 16;
        radius: 4;
        Rectangle {
            color: textcolor;
            visible: control.checked
            width: parent.width / 2
            height: parent.height / 2
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2
            radius: 2
        }
        SequentialAnimation {
            id: animation_scalebounce;
            PropertyAnimation {
                target: checkboxIndicator
                property: "scale"
                to: 1.2
                duration: 100;
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation {
                target: checkboxIndicator
                property: "scale"
                to: 1.0
                duration: 100;
                easing.type: Easing.InOutQuad
            }
        }
        SequentialAnimation {
            id: animation_colorfadeinout;
            ColorAnimation {
                target: checkboxIndicator;
                property: "color";
                to: accentcolor;
                duration: 100;
            }
            ColorAnimation {
                target: checkboxIndicator;
                property: "color";
                to: primarycolor;
                duration: 100;
            }
        }
    }

    Rectangle {
        id: checkboxContent;
        anchors.left: checkboxIndicator.right;
        anchors.leftMargin: 3;
        Image {
            id: ico;
            width: iconsize;
            height: iconsize;
            source: iconsource;
            smooth: true;
            antialiasing: true; 
        }
        Text {
            text: labeltext;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
            color: textcolor;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
            anchors.left: ico.right;
            anchors.leftMargin: 3;
        } 
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { checkboxIndicator.color = Qt.lighter(primarycolor, 1.5); }
        onExited: { checkboxIndicator.color = primarycolor; }
        onClicked: { checked = !checked; animation_scalebounce.start(); animation_colorfadeinout.start(); }
        Rectangle {
            anchors.fill: parent;
            color: "#FFFF00"
            visible: false;
        }
    }
}
