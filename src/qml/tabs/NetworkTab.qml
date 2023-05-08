import QtQuick 2.15
import Network 1.0

import "network" as NetworkTab

Item {
    NetworkTab.SocketConsole {
        name: "КОНСОЛЬ ТЕЛЕМЕТРИИ";
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.margins: 5;
        width: 400;
        height: 400;
    }

//    ImRenderLayer { id: lyo_ImGUIWindow;
//        anchors.fill: parent;
//        anchors.topMargin: 15;
//        focus: true;

//        enabled: true;
//        z: 1000;
//    }

//    ImDebugConsole { id: imgui_DebugConsole; }

//    Connections {
//        target: lyo_ImGUIWindow;
//        function onFrame() { imgui_DebugConsole.frame(); }
//    }

//    Connections {
//        target: Network;
//        function onTelsock(data) { imgui_DebugConsole.telsockAppend(data); }
//        function onFeedbacksock(data) { imgui_DebugConsole.feedbacksockAppend(data); }
//    }
}
