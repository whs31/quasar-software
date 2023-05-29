import QtQuick 2.15
import QtQuick3D 1.15
import Theme 1.0

Rectangle {
    property color topColor: Theme.color("color0");
    property color bottomColor: Theme.color("orange");

    color: Theme.color("dark1");

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

            materials: [ DefaultMaterial {
                    diffuseColor: topColor;
                }
            ]
        }
    }
}
