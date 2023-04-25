import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "layouts" as Layouts

Window { id: root;
    width: 800;
    height: 600;
    visible: true;
    color: "#202329";

    Component.onCompleted: {
        show();
    }

    FontLoader { id: font_Main; source: "qrc:/Overpass.ttf"; }
    property string s_FontMain: font_Main.name;

    Layouts.TelemetryLayout { id: lyo_Telemetry;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.margins: 6;
        width: 300;
        height: 230;
    }
}
