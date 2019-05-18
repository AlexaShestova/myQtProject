import QtQuick 2.8
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 720
    title: qsTr("My Game")

    menuBar: MenuBar {
            Menu {
                title: qsTr("&Game")
                Action {
                    text: qsTr("&New...")
                    onTriggered: { MyController.startGame(); }
                }
                Action {
                    text: qsTr("&Open...")
//                onTriggered: openFileDialog.open()
                }
                Action {
                    text: qsTr("&Save")
                    onTriggered: saveGame();
                }
                Action {
                    text: qsTr("Save &As...")
//                    onTriggered: saveFileDialog.open()
                }
                MenuSeparator { }
                Action {
                    text: qsTr("&Quit")
                    onTriggered: Qt.quit()
                }


            }
            Menu {
                title: qsTr("&Settings")
                Action {
                    text: qsTr("&Game board")
                    onTriggered:{
                        settingsWindow.updateSettings();
                        settingsWindow.visible = true;
                    }
                }
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

    function saveGame()
    {
        var date = new Date();
        var fileName = date.getYear() + "-" + date.getMonth() + "-" +
                + date.getDay() + "-" + date.getHours() + "-" + date.getMinutes() + ".json";
        MyController.saveGame(fileName)//File()
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

        Text {
            id: label
            height: 50
            text: (MyController.isFirstPlayer) ? "Player 1" : "Player 2"
            anchors.left: root.left
            anchors.right: root.right
            anchors.top: root.top
            font.pointSize: 30
            horizontalAlignment: (MyController.isFirstPlayer ) ? Text.AlignLeft : Text.AlignRight
            color: (MyController.isFirstPlayer ) ? "yellow" : "blue"
        }

        Text {
            height: 50
            text: MyController.countFirstColor + " : " + MyController.countSecondColor
            anchors.left: root.left
            anchors.right: root.right
            anchors.top: label.bottom
            font.pointSize: 20
            horizontalAlignment: Text.AlignHCenter
//            color: (MyController.isFirstPlayer ) ? "yellow" : "blue"
        }

        Grid {
            id: grid
            width: window.width * 0.7
            height: window.height * 0.7
            columns: MyData.columns
            rows:  MyData.rows
            anchors.verticalCenter: root.verticalCenter
            anchors.horizontalCenter: root.horizontalCenter
            columnSpacing: 5
            rowSpacing: 5

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
                    width: grid.width / MyData.columns
                    height: grid.height / MyData.rows
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
                            if(MyController.checkRect(index))
                            {
                                MyController.process(index);

                                if(!MyController.checkPole())
                                    dialog_gameOver.open();
                            }
                            else
                                dialog_warning.open()//visible = true
                        }
                    }
                }
                model: MyData


            }
        }
        Dialog {
            id: dialog_warning
            title: "WARNING"
//            standardButton: Dialog.Ok
//            contentWidth: grid.width

            Label{ text: "Выберите другое поле!" }

            onAccepted: console.log("Ok clicked")
        }

        Dialog {
            id: dialog_gameOver
            title: "WARNING"
//            standardButton: Dialog.Ok
//            contentWidth: grid.width

            Label{ text: "Game Over! "}

            onAccepted: {
                MyController.startGame();
                console.log("Ok clicked")
            }
        }
//        FileDialog
//        {
//            id: openFileDialog
////            visible: false
////            modality: Qt.WindowModal
////            selectMultiple: false
////            selectExisting: true
////            selectFolder: false
////            nameFilters: [ "Font files (*.txt)" ]
////            title: qsTr("Select file")

////            onAccepted:
////            {
////                console.log( "open file accepted" )
////                fileUrl.toString()

////            }
//        }
//        FileDialog
//        {
//            id: saveFileDialog
////            visible: false
//            modality: Qt.WindowModal
//            selectMultiple: false
//            selectExisting: true
//            selectFolder: false
//            nameFilters: [ "Font files (*.txt)" ]
//            title: qsTr("Select fils")

//            onAccepted:
//            {
//                console.log( "save file accepted" )
//                fileUrl.toString()

//            }
//        }
        SettingsDialog
        {
            id:settingsWindow
            title: qsTr("Settings")
            onAccepted:
            {
                MyController.startGame();
            }
        }
    }

}
