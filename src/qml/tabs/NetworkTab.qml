import QtQuick 2.15
import Network 1.0
import ImGUI 1.0

Item {
    ImRenderLayer { id: lyo_ImGUIWindow;
        anchors.fill: parent;
        focus: true;

        enabled: root.i_CurrentTabAlias === 3;
        z: 1000;
    }

    ImDebugConsole { id: imgui_DebugConsole; }

    Connections {
        target: lyo_ImGUIWindow;
        function onFrame() { imgui_DebugConsole.frame(); }
    }

    Connections {
        target: Network;
        function onTelsock(data) { imgui_DebugConsole.telsockAppend(data); }
        function onFeedbacksock(data) { imgui_DebugConsole.feedbacksockAppend(data); }
    }
}
