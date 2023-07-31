import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

import "./sidepanel" as Side

Drawer {
    id: drawer
    property int selectedIndex: 0

    SwipeView {
        currentIndex: selectedIndex
        interactive: false
        anchors.fill: parent
        contentWidth: width
        contentHeight: height
        clip: true

        ListView {
            model: ListModel {
                ListElement {
                    index: 0
                    sectionName: "Настройки программы"
                    iconPath: "qrc:/icons/vector/common/settings.svg"
                    shortDescription: "Сетевые параметры и конфигурация приложения"
                    wip: false
                    accentColor: 1
                }

                ListElement {
                    index: 1
                    sectionName: "Менеджер сессий"
                    iconPath: "qrc:/icons/vector/common/warning.svg"
                    shortDescription: "Сохранение и загрузка состояний приложения"
                    wip: true
                    accentColor: 2
                }
            }
            delegate: ItemDelegate {
                required property int index
                required property string sectionName
                required property string iconPath
                required property string shortDescription
                required property bool wip
                required property int accentColor

                width: parent.width
                text: sectionName
                enabled: !wip
                height: 60
                opacity: enabled ? 1.0 : 0.4
                icon {
                    source: iconPath
                    color: accentColor === 1 ? ColorTheme.active.color(ColorTheme.Accent)
                                             : ColorTheme.active.color(ColorTheme.Orange)
                }

                font {
                    pixelSize: 15
                    weight: Font.Bold
                    capitalization: Font.AllUppercase
                }
                Material.foreground: accentColor === 1 ? ColorTheme.active.color(ColorTheme.Accent)
                                                       : ColorTheme.active.color(ColorTheme.Orange)

                onPressed: selectedIndex = index + 1

                Label {
                    anchors {
                        left: parent.left
                        leftMargin: 56
                        bottom: parent.bottom
                        bottomMargin: 3
                    }

                    text: parent.shortDescription
                    font {
                        pixelSize: 12
                        weight: Font.DemiBold
                    }
                    color: ColorTheme.active.color(ColorTheme.Subtext)
                }
            }
        }

        Side.SettingsTab {
        }
    }
}
