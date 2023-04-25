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
