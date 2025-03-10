import QtQuick

Item {
    id: _item2
    width: 240
    height: 55
    anchors.horizontalCenter: parent.horizontalCenter
    Text {
        id: _text3
        x: 50
        width: 100
        height: 16
        color: "#092e24"
        text: qsTr("Client Server")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
        font.weight: Font.ExtraBold
        font.family: "Tahoma"
    }
    
    Rectangle {
        id: rectangle3
        x: 165
        width: 23
        height: 22
        color: "#ffa7a7"
        radius: 11
        anchors.verticalCenter: parent.verticalCenter
    }
}
