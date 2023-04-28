import QtQuick 2.15
import Network 1.0
import ImGUI 1.0

Item {
    ImRenderLayer { id: lyo_ImGUIWindow;
        anchors.fill: parent;
        focus: true;

        enabled: root.i_CurrentTabAlias === 2;
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
    }
}
