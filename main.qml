import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.elmsoft.qmlcomponents 1.0

ApplicationWindow {
    id: topLevel

    title: qsTr("Hello World")
    width: 1000
    height: 480
    visible: true

    property int trackHeight: 50

    Component.onCompleted: {
        outerTrackLeft.section.connectSection(outerSwitchLeft.commonSection, 3)
        outerTrackLeft.section.connectSection(outerTrackRight.section, 3)
        outerSwitchLeft.rightSection.connectSection(outerTrackMiddle.section, 3)
        outerTrackMiddle.section.connectSection(outerSwitchRight.rightSection, 3)
        outerSwitchRight.commonSection.connectSection(outerTrackRight.section, 3)

        innerTrackLeft.section.connectSectionReversed(innerSwitchLeft.rightSection)
        innerTrackLeft.section.connectSection(innerTrackRight.section, 3)
        innerSwitchLeft.commonSection.connectSectionReversed(innerTrackMiddle.section, 3)
        innerTrackMiddle.section.connectSection(innerStationSwitch.rightSection, 3)
        innerStationSwitch.commonSection.connectSectionReversed(innerSwitchRight.commonSection, 3)
        innerSwitchRight.rightSection.connectSectionReversed(innerTrackRight.section, 3)

        outerSwitchLeft.leftSection.connectSectionReversed(innerSwitchLeft.leftSection, 3)
        outerSwitchRight.leftSection.connectSectionReversed(innerSwitchRight.leftSection, 3)
    }

    Rectangle {
        id: powerSupply2
        x: 20
        width: 20
        height: 20
        color: "blue"

        PowerSupply {
            leftVoltage: 3
            rightVoltage: 0
            connectedSection: innerTrackLeft.section
        }
    }

    Rectangle {
        id: powerSupply
        width: 20
        height: 20
        color: "green"

        PowerSupply {
            leftVoltage: 2
            rightVoltage: 0
            connectedSection: outerTrackLeft.section
        }
    }

    Rectangle {
        id: outerTrackSection

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.right: parent.right

        height: trackHeight

        TrackSectionItem {
            id: outerTrackLeft

            width: 50

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        PointSectionItem {
            id: outerSwitchLeft

            anchors.left: outerTrackLeft.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            width: 100
            direction: 1

            MouseArea {
                anchors.fill: parent
                onClicked: outerSwitchLeft.direction = !outerSwitchLeft.direction
            }
        }

        TrackSectionItem {
            id: outerTrackMiddle

            anchors.left: outerSwitchLeft.right
            anchors.right: outerSwitchRight.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        PointSectionItem {
            id: outerSwitchRight

            anchors.right: outerTrackRight.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            direction: 1
            width: 100

            transform: Rotation { origin.x: outerSwitchRight.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

            MouseArea {
                anchors.fill: parent
                onClicked: outerSwitchRight.direction = !outerSwitchRight.direction
            }
        }

        TrackSectionItem {
            id: outerTrackRight

            width: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
    }

    Rectangle {
        id: innerTrackSection

        anchors.bottom: outerTrackSection.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: trackHeight

        TrackSectionItem {
            id: innerTrackLeft

            width: 50

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        PointSectionItem {
            id: innerSwitchLeft

            anchors.left: innerTrackLeft.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            width: 100
            direction: 1

            rotation: 180

            MouseArea {
                anchors.fill: parent
                onClicked: innerSwitchLeft.direction = !innerSwitchLeft.direction
            }
        }

        TrackSectionItem {
            id: innerTrackMiddle

            anchors.left: innerSwitchLeft.right
            anchors.right: innerStationSwitch.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        PointSectionItem {
            id: innerStationSwitch

            anchors.right: innerSwitchRight.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            direction: 1
            width: 100

            transform: Rotation { origin.x: innerSwitchRight.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

            MouseArea {
                anchors.fill: parent
                onClicked: innerStationSwitch.direction = !innerStationSwitch.direction
            }
        }

        PointSectionItem {
            id: innerSwitchRight

            anchors.right: innerTrackRight.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            direction: 1
            width: 100

            rotation: 180

            transform: Rotation { origin.x: innerSwitchRight.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

            MouseArea {
                anchors.fill: parent
                onClicked: innerSwitchRight.direction = !innerSwitchRight.direction
            }
        }

        TrackSectionItem {
            id: innerTrackRight

            width: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
    }
}
