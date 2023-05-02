import QtQuick 2.15
import QtQuick3D 1.15
import Telemetry 1.0

View3D { id: c_3DView;
    focus: true;
    Keys.onPressed: (event)=> {
                        if(event.key === Qt.Key_L)
                            console.log("Debug key pressed");
                        if (event.key === Qt.Key_D)
                            root.yaw = 1;
                        if (event.key === Qt.Key_A)
                            root.yaw = -1;
                        if (event.key === Qt.Key_W)
                            root.pitch = 1;
                        if (event.key === Qt.Key_S)
                            root.pitch = -1;
                        if (event.key === Qt.Key_Q)
                            root.roll = -1;
                        if (event.key === Qt.Key_E)
                            root.roll = 1;
    }
    Keys.onReleased: (event)=> {
                         if (event.key === Qt.Key_D)
                             root.yaw = 0;
                         if (event.key === Qt.Key_A)
                             root.yaw = 0;
                         if (event.key === Qt.Key_W)
                             root.pitch = 0;
                         if (event.key === Qt.Key_S)
                             root.pitch = 0;
                         if (event.key === Qt.Key_Q)
                             root.roll = 0;
                         if (event.key === Qt.Key_E)
                             root.roll = 0;
    }

    camera: camera;


    environment: SceneEnvironment {
        id: sceneEnvironment;
        clearColor: "#222222";
        backgroundMode: SceneEnvironment.Color;
        antialiasingMode: SceneEnvironment.SSAA;
        antialiasingQuality: SceneEnvironment.VeryHigh;
    }

    PerspectiveCamera {
        id: camera;
        position: Qt.vector3d(mesh_HelicopterMesh.fl_uavX, mesh_HelicopterMesh.fl_uavY + 40, mesh_HelicopterMesh.fl_uavZ + 100);
        eulerRotation.x: -10;
    }

    DirectionalLight {
        eulerRotation.x: -30;
    }

    Node {
        id: node_HelicopterNode;

        NumberAnimation {
            target: mesh_HelicopterMesh
            property: "fl_uavZ";
            to: -100000;
            duration: 10000;
            easing.type: Easing.InOutQuad;
            running: true;
        }

        Model { id: mesh_HelicopterMesh;
            property real fl_uavX: 0;
            property real fl_uavY: 0;
            property real fl_uavZ: 0;

            source: "qrc:/meshes/model.mesh";
            position: Qt.vector3d(fl_uavX, fl_uavY, fl_uavZ);

            eulerRotation.x: Telemetry.pitch;
            eulerRotation.y: -Telemetry.course + 180;
            eulerRotation.z: Telemetry.roll;

            DefaultMaterial {
                id: mat_Placeholder;
                diffuseColor: "#d8dee9";
            }
            materials: [
                mat_Placeholder
            ]
        }

//        Model {
//            source: "#Rectangle"
//            scale: Qt.vector3d(100000, 100000, 1);
//            position: Qt.vector3d(0, 0, -10);
//            eulerRotation.x: -90;
//            materials: DefaultMaterial {
//                diffuseMap: Texture {
//                    source: "qrc:/images/placeholder.jpg"
//                    tilingModeHorizontal: Texture.Repeat;
//                    tilingModeVertical: Texture.Repeat;
//                    scaleU: 100000;
//                    scaleV: 100000;
//                }
//                normalMap: Texture {
//                    source: "images/grass_n.jpg";
//                }
//                bumpAmount: 0.6;
//            }
//        }
    }
}
