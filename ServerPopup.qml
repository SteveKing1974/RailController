import QtQuick 2.0

MouseArea {
    id: selectServerDlg

    anchors.fill: parent

    z: 2
    property QtObject controllerObj: null

    Rectangle {
        color: "black"
        opacity: 0.5
        anchors.fill: parent
    }


    Rectangle {
        id: clientsRect

        anchors.centerIn: parent

        color: "white"
        width: 200
        height: 200

        border.color: "black"
        border.width: 4
        radius: 10

        ListView {

            anchors.fill: parent
            anchors.margins: 30

            header: Text {
                text: "Refresh"
                height: 30
                color: "black"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        controllerObj.refreshClients()
                    }
                }
            }

            model: controllerObj.serverModel
            delegate: Text {
                text: ipAddress
                height: 30
                color: "black"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        controllerObj.connectToServer(ipAddress)
                    }
                }
            }
        }
    }
}
