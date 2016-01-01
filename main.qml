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

    Component.onCompleted: {
        outerSwitchLeft.leftSection.connectSectionReversed(innerSwitchLeft.leftSection, 3)
        outerSwitchRight.leftSection.connectSectionReversed(innerSwitchRight.leftSection, 3)
        stationInnerMiddle.section.connectSection(stationHeadShuntLeft.section, 3)

        innerStationSwitch.leftSection.connectSectionReversed(stationOuterEntrance.leftSection, 3)

        stationOuterToInner.leftSection.connectSectionReversed(stationInnerLoopSwitchRight.leftSection, 3)
        stationOuterLoopSwitchLeft.leftSection.connectSectionReversed(stationInnerLoopSwitchLeft.leftSection, 3)

        // Right section items
        stationOuterSidingPoints.leftSection.connectSectionReversed(rightSidingSwitch2.commonSection, 3)

        rightSidingSwitch2.leftSection.connectSectionReversed(rightSiding2.section, 3)
        rightSidingSwitch2.rightSection.connectSectionReversed(rightSidingBreak.leftSection, 3)

        rightSidingBreak.rightSection.connectSection(rightSidingUpper.section, 3)
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

            Component.onCompleted: {
                outerTrackLeft.section.connectSection(outerSwitchLeft.commonSection, 3)
                outerTrackLeft.section.connectSection(outerTrackRight.section, 3)
                outerSwitchLeft.rightSection.connectSection(outerTrackMiddle.section, 3)
                outerTrackMiddle.section.connectSection(outerSwitchRight.rightSection, 3)
                outerSwitchRight.commonSection.connectSection(outerTrackRight.section, 3)
            }

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

            Component.onCompleted: {
                innerTrackLeft.section.connectSectionReversed(innerSwitchLeft.rightSection)
                innerTrackLeft.section.connectSection(innerTrackRight.section, 3)
                innerSwitchLeft.commonSection.connectSectionReversed(innerTrackMiddle.section, 3)
                innerTrackMiddle.section.connectSection(innerStationSwitch.rightSection, 3)
                innerStationSwitch.commonSection.connectSectionReversed(innerSwitchRight.commonSection, 3)
                innerSwitchRight.rightSection.connectSectionReversed(innerTrackRight.section, 3)
            }

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
            anchors.leftMargin: 20
            anchors.rightMargin: 0

            height: trackHeight

            Component.onCompleted: {
                stationHeadShuntLeft.section.connectSection(stationOuterLoopSwitchLeft.commonSection, 3)
                stationOuterLoopSwitchLeft.rightSection.connectSection(stationOuterMiddle.section, 3)
                stationOuterMiddle.section.connectSection(stationOuterToInner.rightSection, 3)
                stationOuterToInner.commonSection.connectSectionReversed(stationOuterEntrance.commonSection)
                stationOuterEntrance.rightSection.connectSectionReversed(stationOuterSidingPoints.commonSection)
                stationOuterSidingPoints.rightSection.connectSection(stationOuterSidingRight.section, 3)
            }

            TrackSectionItem {
                id: stationHeadShuntLeft

                width: 270

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

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationOuterSidingPoints.direction = !stationOuterSidingPoints.direction
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
            anchors.leftMargin: 20
            anchors.rightMargin: 0

            height: trackHeight

            Component.onCompleted: {
                stationInnerLoopSwitchLeft.commonSection.connectSectionReversed(stationInnerMiddle.section, 3)
                stationInnerLoopSwitchRight.commonSection.connectSectionReversed(stationInnerMiddle.section, 3)
                stationInnerLoopSwitchRight.rightSection.connectSectionReversed(stationInnerHeadShuntRightBreak.leftSection, 3)
                stationInnerHeadShuntRightBreak.rightSection.connectSection(stationInnerHeadShuntRight.section, 3)

                leftSidingSwitch.commonSection.connectSectionReversed(stationInnerLoopSwitchLeft.rightSection, 3)
                leftSidingSwitch.rightSection.connectSection(stationSiding1Left.section, 3)

                leftSidingSwitch.leftSection.connectSectionReversed(leftSidingSwitch2.commonSection, 3)

                leftSidingSwitch2.leftSection.connectSectionReversed(leftSiding2.section, 3)

                leftSidingBreak.leftSection.connectSection(leftSidingUpper.section, 3)
                leftSidingSwitch2.rightSection.connectSectionReversed(leftSidingBreak.rightSection, 3)

            }

            TrackSectionItem {
                id: stationSiding1Left

                width: 170

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
                anchors.leftMargin: 143
                anchors.top: parent.top
                anchors.topMargin: -53
                anchors.bottomMargin: 53
                anchors.bottom: parent.bottom
                direction: 1
                width: 100

                rotation: 225

                MouseArea {
                    anchors.fill: parent
                    onClicked: leftSidingSwitch2.direction = !leftSidingSwitch2.direction
                }
            }
            TrackSectionItem {
                id: leftSiding2

                width: 190
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: -32
                anchors.bottomMargin: 40
                anchors.bottom: parent.bottom
            }

            Rectangle {
                color: "white"

                width: 175
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: -72
                anchors.bottomMargin: 70
                anchors.bottom: parent.bottom
                TrackSectionItem {
                    id: leftSidingUpper

                    anchors.left: parent.left
                    anchors.right: leftSidingBreak.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                }

                BreakSectionItem {
                    id: leftSidingBreak

                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    width: 50

                    MouseArea {
                        anchors.fill: parent
                        onClicked: leftSidingBreak.enabled = !leftSidingBreak.enabled
                    }
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

//                Rectangle {
//                    anchors.fill: parent
//                    color: "yellow"
//                }

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

                anchors.right: stationInnerHeadShuntRightBreak.left
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


            BreakSectionItem {
                id: stationInnerHeadShuntRightBreak

                anchors.right: stationInnerHeadShuntRight.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: 50

                MouseArea {
                    anchors.fill: parent
                    onClicked: stationInnerHeadShuntRightBreak.enabled = !stationInnerHeadShuntRightBreak.enabled
                }
            }

            TrackSectionItem {
                id: stationInnerHeadShuntRight

                width: 50
                anchors.rightMargin: 200
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

                    anchors.left: rightSidingBreak.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                }

                BreakSectionItem {
                    id: rightSidingBreak

                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    width: 50

                    MouseArea {
                        anchors.fill: parent
                        onClicked: rightSidingBreak.enabled = !rightSidingBreak.enabled
                    }
                }
            }
        }
    }
}
