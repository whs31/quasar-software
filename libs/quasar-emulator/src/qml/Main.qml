import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15

import Telemetry 1.0
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

    property int pitch: 0;
    property int roll: 0;
    property int yaw: 0;
    function updateAxes() {
        if(pitch === -1)
            Telemetry.pitch -= 1;
        if(pitch === 1)
            Telemetry.pitch += 1;
        if(roll === -1)
            Telemetry.roll -= 1;
        if(roll === 1)
            Telemetry.roll += 1;
        if(yaw === -1)
            Telemetry.course -= 1;
        if(yaw === 1)
            Telemetry.course += 1;
    }

    Timer { interval: 20; repeat: true; running: true; onTriggered: updateAxes(); }

    View3D { id: c_3DView;
        focus: true;
        Keys.onPressed: (event)=> {
                            if (event.key === Qt.Key_D)
                                yaw = 1;
                            if (event.key === Qt.Key_A)
                                yaw = -1;
                            if (event.key === Qt.Key_W)
                                pitch = 1;
                            if (event.key === Qt.Key_S)
                                pitch = -1;
                            if (event.key === Qt.Key_Q)
                                roll = -1;
                            if (event.key === Qt.Key_E)
                                roll = 1;
        }
        Keys.onReleased: (event)=> {
                             if (event.key === Qt.Key_D)
                                 yaw = 0;
                             if (event.key === Qt.Key_A)
                                 yaw = 0;
                             if (event.key === Qt.Key_W)
                                 pitch = 0;
                             if (event.key === Qt.Key_S)
                                 pitch = 0;
                             if (event.key === Qt.Key_Q)
                                 roll = 0;
                             if (event.key === Qt.Key_E)
                                 roll = 0;
        }

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
            position: Qt.vector3d(0, 40, 100);
            eulerRotation.x: -10;
        }

        DirectionalLight {
            eulerRotation.x: -30;
        }

        Node {
            id: node_HelicopterNode;

            Model {
                id: mesh_HelicopterMesh;
                source: "qrc:/meshes/model.mesh";

                eulerRotation.x: Telemetry.pitch;
                eulerRotation.y: Telemetry.course - 180;
                eulerRotation.z: Telemetry.roll;

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
