import QtQuick 2.8
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 720
    title: qsTr("My Game")
    menuBar: MenuBar {
            Menu {
                title: qsTr("&Game")
                Action { text: qsTr("&New...")
                }
                Action { text: qsTr("&Open...") }
                Action { text: qsTr("&Save") }
                Action { text: qsTr("Save &As...") }
                MenuSeparator { }
                Action { text: qsTr("&Quit") }


            }
            Menu {
                title: qsTr("&Settings")
                Action { text: qsTr("&Game board") }
                Action { text: qsTr("&game difficulty") }
            }
            Menu {
                title: qsTr("&Help")
                Action { text: qsTr("&About") }
            }
        }
    Component.onCompleted: {
        //console.log(MyData.size)
    }

//    menuBar: MenuBar {
//        Menu {
//            title: "Game"
//            MenuItem { text: "newGame" }
//            MenuItem { text: "loadGame" }
//        }

//        Menu {
//            title: "Settings"
//            MenuItem { text: "Colors" }
//            MenuItem { text: "Players" }
//        }
//    }

    Item {
        id: root
        anchors.fill: parent

        property int widthRect : 80


        Text {
            height: 50
            text: (grid.isFirstPlayer) ? "Player 1" : "Player 2"
            anchors.left: root.left
            anchors.right: root.right
            anchors.top: root.top
            font.pointSize: 30
            horizontalAlignment: (grid.isFirstPlayer ) ? Text.AlignLeft : Text.AlignRight
            color: (grid.isFirstPlayer ) ? "yellow" : "blue"
        }


        Grid {
            id: grid
            width: window.height * 0.7
            height: width
            columns: MyData.size
            anchors.verticalCenter: root.verticalCenter
            anchors.horizontalCenter: root.horizontalCenter
            columnSpacing: 5
            rowSpacing: 5
            property bool isFirstPlayer: true

            Repeater{

                Rectangle {
                    id: rectDelegate
                    Behavior on color {
                        SequentialAnimation {

                            PauseAnimation {
                                duration: 0//Delay
                            }
                            ColorAnimation {
                                duration: 500
                            }
                        }


                    }
                    width: grid.width / MyData.size
                    height: width
                    color: ColorData
                    Text {
                        font.pointSize: 30
                        anchors.centerIn: parent
                        text: IntData
                    }
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent

                        onClicked: {
                            if(MyData.checkRect(index, grid.isFirstPlayer))
                            {
                                MyData.process(index, grid.isFirstPlayer);
                                grid.isFirstPlayer = !grid.isFirstPlayer;
                            }
                            else
                                dialog_warning.visible = true
                        }
                    }
                }
                model: MyData


            }
        }
        Dialog {
            id: dialog_warning
            title: "WARNING"
            standardButtons: Dialog.Ok
            contentWidth: grid.width

            Label{ text: "Выберите другое поле!" }

            onAccepted: console.log("Ok clicked")
        }
    }

}
