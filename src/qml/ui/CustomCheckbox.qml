import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property int iconsize: 16;
    property string iconsource: "qrc:/ui-resources/white/close.png";
    
    property string labeltext: "Not assigned";
    property color primarycolor: "#dae1e5";
    property color accentcolor: "#204040";

    property bool checked: false;

    width: childrenRect.width; 
    height: childrenRect.height;
    
    id: control;
    antialiasing: true; 
            
    Rectangle {
        id: checkboxIndicator;
        color: accentcolor;
        anchors.left: parent.left;
        //anchors.horizontalCenter: parent.horizontalCenter;
        
        implicitWidth: 16;
        implicitHeight: 16;
        radius: 4;
        Rectangle {
            color: primarycolor;
            visible: control.checked
            width: parent.width / 2
            height: parent.height / 2
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2
            radius: 2
        }
        MouseArea {
            id: controlMouseArea;
            hoverEnabled: true;
            anchors.fill: parent
            onClicked: { checked = !checked; }
        }
    }

    Rectangle {
        id: checkboxContent;
        anchors.left: checkboxIndicator.right;
        Image {
            id: ico;
            width: iconsize;
            height: iconsize;
            source: iconsource;
            smooth: true;
        }
        Text {
            text: labeltext;
            font.capitalization: Font.MixedCase; 
            font.pixelSize: 11;
            color: primarycolor;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
            anchors.left: ico.right;
            anchors.leftMargin: 3;
        }
    }
    
}