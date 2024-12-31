import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#b5c3af"
    title: qsTr("Hello World")

    Button {
        x: 6
        y: 0
        text: "Bla"
        width: 200
        height: 50
        onClicked: backend.callMe()
    }

    Rectangle{
        anchors.centerIn: parent
        width: parent.width
        height: 200
        color: "#e1eddb"
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenterOffset: 0
        ListView{
            x: 8
            y: 8
            width: 500
            height: 177
            model: backend.logList
            delegate: Text {
                text: modelData
            }
        }
    }




}
