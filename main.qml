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

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

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

        stationHeadShuntLeft.section.connectSection(stationOuterLoopSwitchLeft.commonSection, 3)
        stationOuterLoopSwitchLeft.rightSection.connectSection(stationOuterMiddle.section, 3)
        stationOuterMiddle.section.connectSection(stationOuterToInner.rightSection, 3)
        stationOuterToInner.commonSection.connectSectionReversed(stationOuterSidingsRight.commonSection)
        stationOuterSidingsRight.rightSection.connectSectionReversed(stationOuterSidingRight.section)
    }

    Rectangle {
        id: powerSupply2
        x: 20
        width: 20
        height: 20
        color: "blue"

        PowerSupply {
            leftVoltage: 2
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
            leftVoltage: 3
            rightVoltage: 0
            connectedSection: outerTrackLeft.section
        }
    }
    Rectangle {
        id: powerSupply3
        x: 40
        width: 20
        height: 20
        color: "red"

        PowerSupply {
            leftVoltage: 1
            rightVoltage: 0
            connectedSection: stationHeadShuntLeft.section
        }
    }


    Item {
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        Item {
            id: outerTrackSection

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.left: parent.left
            anchors.right: parent.right

            height: trackHeight

            TrackSectionItem {
                id: outerTrackLeft

                width: 100

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

                width: 100
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }

        Item {
            id: innerTrackSection

            anchors.bottom: outerTrackSection.top
            anchors.left: parent.left
            anchors.right: parent.right

            height: trackHeight

            TrackSectionItem {
                id: innerTrackLeft

                width: 100

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

                width: 100
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }

        Item {
            id: stationOuterSection

            anchors.bottom: innerTrackSection.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 100
            anchors.rightMargin: 0

            height: trackHeight

            TrackSectionItem {
                id: stationHeadShuntLeft

                width: 150

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PointSectionItem {
                id: stationOuterLoopSwitchLeft

                anchors.left: stationHeadShuntLeft.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: 100
                direction: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationOuterLoopSwitchLeft.direction = !stationOuterLoopSwitchLeft.direction
                }
            }

            TrackSectionItem {
                id: stationOuterMiddle

                anchors.left: stationOuterLoopSwitchLeft.right
                anchors.right: stationOuterToInner.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PointSectionItem {
                id: stationOuterToInner

                anchors.right: stationOuterEntrance.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                transform: Rotation { origin.x: stationOuterToInner.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationOuterToInner.direction = !stationOuterToInner.direction
                }
            }

            PointSectionItem {
                id: stationOuterEntrance

                anchors.right: stationOuterSidingPoints.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                rotation: 180

                transform: Rotation { origin.x: stationOuterEntrance.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationOuterEntrance.direction = !stationOuterEntrance.direction
                }
            }

            PointSectionItem {
                id: stationOuterSidingPoints

                anchors.right: stationOuterSidingRight.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                //rotation: 180

                //transform: Rotation { origin.x: stationInnerSidingRight1.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationInnerSidingRight1.direction = !stationInnerSidingRight1.direction
                }
            }

            TrackSectionItem {
                id: stationOuterSidingRight

                width: 100
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }

        Item {
            id: stationInnerSection

            anchors.bottom: stationOuterSection.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 100
            anchors.rightMargin: 0

            height: trackHeight

            TrackSectionItem {
                id: stationSiding1Left

                width: 50

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PointSectionItem {
                id: leftSidingSwitch

                anchors.left: stationSiding1Left.right

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                transform: Rotation { origin.x: leftSidingSwitch.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: leftSidingSwitch.direction = !leftSidingSwitch.direction
                }
            }

            PointSectionItem {
                id: leftSidingSwitch2

                anchors.left: parent.left
                anchors.leftMargin: 23
                anchors.top: parent.top
                anchors.topMargin: -53
                anchors.bottomMargin: 53
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                rotation: 225
                //transform: Rotation { origin.x: leftSidingSwitch2.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: leftSidingSwitch2.direction = !leftSidingSwitch2.direction
                }
            }
            TrackSectionItem {
                id: leftSiding2

                width: 70
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: -32
                anchors.bottomMargin: 40
                anchors.bottom: parent.bottom
            }

            Rectangle {
                color: "white"

                width: 57
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: -72
                anchors.bottomMargin: 70
                anchors.bottom: parent.bottom
                TrackSectionItem {
                    id: leftSidingUpper

                    anchors.fill: parent

                }
            }

            PointSectionItem {
                id: stationInnerLoopSwitchLeft

                anchors.left: leftSidingSwitch.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: 100
                direction: 1

                rotation: 180

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationInnerLoopSwitchLeft.direction = !stationInnerLoopSwitchLeft.direction
                }
            }

            TrackSectionItem {
                id: stationInnerMiddle

                anchors.left: stationInnerLoopSwitchLeft.right
                anchors.right: stationInnerLoopSwitchRight.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PointSectionItem {
                id: stationInnerLoopSwitchRight

                anchors.right: stationInnerHeadShuntRight.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                rotation: 180
                transform: Rotation { origin.x: stationInnerLoopSwitchRight.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationInnerLoopSwitchRight.direction = !stationInnerLoopSwitchRight.direction
                }
            }



            TrackSectionItem {
                id: stationInnerHeadShuntRight

                width: 50
                anchors.rightMargin: 250
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            PointSectionItem {
                id: rightSidingSwitch2

                anchors.right: parent.right
                anchors.rightMargin: 77
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                rotation: 225
                transform: Rotation { origin.x: rightSidingSwitch2.width/2; axis { x: 0; y: 1; z: 0 } angle: 180 }

                MouseArea {
                    anchors.fill: parent
                    onClicked: rightSidingSwitch2.direction = !rightSidingSwitch2.direction
                }
            }
            TrackSectionItem {
                id: rightSiding2

                width: 77
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 21
                anchors.bottomMargin: -14
                anchors.rightMargin: 42
                anchors.bottom: parent.bottom
            }

            Rectangle {
                color: "white"


                width: 77
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: -25
                anchors.bottomMargin: 21
                anchors.rightMargin: 28
                anchors.bottom: parent.bottom
                TrackSectionItem {
                    id: rightSidingUpper

                    anchors.fill: parent

                }
            }
        }
    }
}
