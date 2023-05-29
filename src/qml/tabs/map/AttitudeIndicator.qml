import QtQuick 2.15
import QtQuick3D 1.15
import Theme 1.0

Rectangle {
    color: Theme.color("dark1");
    property real pitch;
    property real roll;
    property real yaw;

    View3D {
        anchors.fill: parent;
        environment: SceneEnvironment {
            clearColor: Theme.color("dark1");
            backgroundMode: SceneEnvironment.Color;
        }

        PerspectiveCamera {
            position: Qt.vector3d(0, 0, 110);
        }

        DirectionalLight  {
            position: Qt.vector3d(0, 0, 0);
        }

        Model {
            position: Qt.vector3d(0, 0, 0);
            source: "#Sphere";
            eulerRotation.x: -pitch;
            eulerRotation.y: yaw;
            eulerRotation.z: roll;
            materials: [
                DefaultMaterial  {
                    diffuseMap: Texture {
                        source: "qrc:/textures/attitude.png";
                        scaleU: 1.0;
                        scaleV: 1.0;
                    }
                }
            ]
        }
    }
}
