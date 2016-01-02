import QtQuick 2.0

import com.elmsoft.qmlcomponents 1.0

MouseArea {
    onClicked: visible = false

    property QtObject lineModel: null

    z: 2

    Rectangle {
        color: "black"
        opacity: 0.5
        anchors.fill: parent
    }

    onVisibleChanged: {
        if (!visible)
        {
            popupContent.modelIndex = -1
            popupContent.v = []
        }
    }

    function selectController(sectionIndex, possibleControllers)
    {
        popupContent.modelIndex = sectionIndex
        popupContent.v = possibleControllers
        visible = true
    }


    Rectangle {
        id: popupRect

        anchors.centerIn: parent

        color: "white"
        width: 200
        height: 200

        border.color: "black"
        border.width: 4
        radius: 10

        ListView {
            id: popupContent

            anchors.fill: parent
            anchors.margins: 30

            property variant v: []
            property int modelIndex: -1

            model: v
            delegate: Text {
                text: lineModel.controllerName(popupContent.v[index])
                height: 30
                color: "black"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        lineModel.changeController(popupContent.modelIndex, popupContent.v[index])
                        selectControllerDlg.visible = false
                    }
                }
            }
        }
    }
}
