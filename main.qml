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

    Controller {
        id: connectionController
    }

    ServerPopup {
        anchors.fill: parent
        controllerObj: connectionController
    }

    TrackCanvas {
        anchors.fill: parent
        enabled: false

        opacity: 0.2
    }
}
