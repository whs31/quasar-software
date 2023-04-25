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

        environment: SceneEnvironment {
            id: sceneEnvironment;
            clearColor: "#202329";
            backgroundMode: SceneEnvironment.Color;
            antialiasingMode: SceneEnvironment.SSAA;
            antialiasingQuality: SceneEnvironment.VeryHigh;
        }

        //renderMode: View3D.Overlay;

        PerspectiveCamera {
            id: camera;
            position: Qt.vector3d(0, 70, 100);
            eulerRotation.x: -30;
        }

        DirectionalLight {
            eulerRotation.x: -30;
        }

        Node {
            id: node_HelicopterNode;

            Model {
                id: mesh_HelicopterMesh;
                source: "qrc:/meshes/model.mesh";

                eulerRotation.y: 180;

                DefaultMaterial {
                    id: mat_Placeholder;
                    diffuseColor: "#d8dee9";
                }
                materials: [
                    mat_Placeholder
                ]
            }
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
