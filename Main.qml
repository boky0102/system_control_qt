import QtQuick
import QtQuick.Controls
import SvgElement 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#b5c3af"
    title: qsTr("Hello World")


    Rectangle{
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height / 4
        color: "#e1eddb"
        transformOrigin: Item.Bottom
        ListView{
            id: logView
            x: 8
            y: 8
            width: 500
            height: parent.height - 20
            focus: false
            model: backend.logList
            delegate: Text {
                text: modelData
            }
            clip: true

            onCountChanged: () => {
                                logView.positionViewAtEnd();
                            }
        }
    }

    Rectangle {
        id: rectangle
        x: 402
        width: 220
        height: 220
        color: "#e9e1aa"
        radius: 8
        border.color: "#27051813"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 30
        anchors.topMargin: 30

        Text {
            id: _text
            width: 156
            height: 50
            text: qsTr("QR code will be displayed here after it has been generated")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            font.underline: false
            font.strikeout: false
            font.bold: true
        }

        SvgElement {
            id: svgItem
            width: 200
            height: 200
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            svgSource: qrCode.svgSource
        }
    }

    Rectangle {
        id: rectangle1
        width: 356
        height: 301
        color: "#b6becd"
        radius: 7
        border.color: "#27051813"
        border.width: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 16
        anchors.topMargin: 31

        Column {
            id: column
            x: 0
            y: 0
            width: rectangle1.width
            height: rectangle1.height
            spacing: 0

            Text {
                id: _text1
                text: qsTr("STATUS")
                anchors.top: parent.top
                anchors.topMargin: 10
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
                font.weight: Font.ExtraBold
            }



            Column {
                id: column1
                width: rectangle1.width
                height: 276
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -10
                padding: 0
                topPadding: 0
                spacing: 0

                Item {
                    id: _item
                    width: 200
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: _text2
                        color: "#041b15"
                        text: qsTr("Backend Server")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 15
                        font.styleName: "Black"
                    }

                    Rectangle {
                        id: backendIndicator
                        x: 122
                        width: 26
                        height: 26
                        color: "#f19797"
                        radius: 13
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                    }

                    BusyIndicator {
                        id: backendSpinner
                        anchors.verticalCenter: backendIndicator.verticalCenter
                        anchors.horizontalCenter: backendIndicator.horizontalCenter
                    }

                    ColorAnimation {
                        from: "#f19797"
                        to: "#5cf77b"
                        duration: 500
                        property: "color"
                        target: backendIndicator
                        id: backendIndicatorAnimation
                    }
                }

                Item {
                    id: _item1
                    width: 200
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: _text3
                        text: qsTr("Client Server")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 15
                        font.styleName: "Black"
                    }

                    Rectangle {
                        id: clientIndicator
                        x: 247
                        y: 125
                        width: 26
                        height: 26
                        color: "#f19797"
                        radius: 13
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                    }

                    BusyIndicator {
                        id: clientSpinner
                        anchors.verticalCenter: clientIndicator.verticalCenter
                        anchors.horizontalCenter: clientIndicator.horizontalCenter
                    }


                    ColorAnimation {
                        from: "#f19797"
                        to: "#5cf77b"
                        duration: 500
                        property: "color"
                        target: clientIndicator
                        id: clientIndicatorAnimation
                    }
                }

                Item {
                    id: _item2
                    width: 200
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: _text4
                        text: qsTr("Ready")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 15
                        font.weight: Font.Black
                    }

                    Rectangle {
                        id: readyIndicator
                        x: 247
                        y: 25
                        width: 26
                        height: 26
                        color: "#f19797"
                        radius: 13
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                    }

                    BusyIndicator {
                        id: readySpinner
                        anchors.verticalCenter: readyIndicator.verticalCenter
                        wheelEnabled: false
                        anchors.horizontalCenter: readyIndicator.horizontalCenter
                    }

                    ColorAnimation {
                        from: "#f19797"
                        to: "#5cf77b"
                        duration: 500
                        property: "color"
                        target: readyIndicator
                        id: readyIndicatorAnimation
                    }
                }


            }

        }
    }

    Connections {
        target: backend
        onClientRunning: () => {
                             //clientIndicator.color = "#5cf77b"
                             clientIndicatorAnimation.start()
                             clientSpinner.running = false

                         }
        onBackendRunning: () => {
                            backendIndicatorAnimation.start()
                            backendSpinner.running = false
                          }
        onServersInitializationSucces: () => {
                                        readyIndicatorAnimation.start()
                                           readySpinner.running = false
                                       }
        onRemoteAddressAvaliable: (address) => {
                                      ipText.text = address
                                  }
    }

    Rectangle {
        id: addressContainer
        x: 400
        width: 200
        height: 68
        color: "#b9efd4"
        radius: 7
        border.color: "#27051813"
        anchors.right: parent.right
        anchors.top: rectangle.bottom
        anchors.rightMargin: 40
        anchors.topMargin: 16

        Column {
            id: column2
            y: 59
            width: addressContainer.width
            height: addressContainer.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: _text5
                text: qsTr("REMOTE CONTROL ADDRESS")
                font.pixelSize: 12
                font.weight: Font.Bold
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                id: ipText
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 18
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }







}
