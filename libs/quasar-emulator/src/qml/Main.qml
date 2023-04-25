import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15

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

    View3D { id: c_3DView;
        anchors.fill: parent;
        camera: camera;
        //renderMode: View3D.Overlay;

        PerspectiveCamera {
            id: camera;
            position: Qt.vector3d(0, 200, 300);
            eulerRotation.x: -30;
        }

        DirectionalLight {
            eulerRotation.x: -30;
        }

        Model { id: model_Cube;
            visible: true
            position: Qt.vector3d(0, 0, 0)
            source: "#Cube"
            materials: [ DefaultMaterial {
                    diffuseMap: Texture {
                        id: texture
                        source: "qrc:/checkers.png"
                    }
                }
            ]
        }
    }

    Layouts.TelemetryLayout { id: lyo_Telemetry;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.margins: 6;
        width: 300;
        height: 230;
    }
}
