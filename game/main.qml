import QtQuick 2.8
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
//import QtQuick 2.2
//  import QtQuick.Dialogs 1.0
ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 790
    title: qsTr("My Game")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Game")
            Action {
                text: qsTr("&New...")
                onTriggered: { newGameWindow.visible = true; }
            }
            Action {
                text: qsTr("&Open...")
                onTriggered: openFileDialog.open()
            }
            Action {
                text: qsTr("&Save")
                onTriggered: saveGame();
            }
            Action {
                text: qsTr("Save &As...")
                onTriggered: saveFileDialog.open()
            }
            MenuSeparator { }

            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }


        }

        MenuBarItem{
            id: settings
            text:  qsTr("Settings")

            onTriggered: {
                settings.focus = false;
                settings.highlighted = false;
                settingsWindow.visible = true;
                settingsWindow.updateSettings();
            }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered: dialogAbout.visible = true
            }
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
            color: (MyController.isFirstPlayer ) ? MyController.firstColor : MyController.secondColor
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
                                duration: IntData*200
                            }
                            ColorAnimation {
                                duration: 500
                            }
                        }
                    }
                    width: grid.width / MyData.columns
                    height: grid.height / MyData.rows
                    color: ColorData
//                    Text {
//                        font.pointSize: 30
//                        anchors.centerIn: parent
//                        text: IntData
//                    }
                    Rectangle
                    {
                        id: warningRect
                        color: "transparent"
                        anchors.fill: parent

                        Behavior on color{
                            ColorAnimation{
                                from: "red"
                                to: "transparent"
                                duration: 700
                                loops: 3
                            }
                        }
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent

                        onClicked: {
                            if(MyController.checkRect(index))
                            {
                                MyController.move(index);

                                if(!MyController.checkField())
                                    dialog_gameOver.open();
                            }
                            else
                            {
                                //                                warningRect.visible = true
                                warningRect.color = "red"
                                //                                dialog_warning.visible = true
                            }
                        }
                    }
                }
                model: MyData


            }
        }
        MessageDialog {
            id: dialog_warning
            icon: StandardIcon.Warning
            title: "WARNING"
            text: "Select another rectangle "

            onAccepted: {
                visible = false;
            }
        }

        MessageDialog {
            id: dialog_gameOver

            icon: StandardIcon.Critical
            title: "Game Over"
            text: {
                var res =  "Game Over! ";
                if(MyController.countFirstColor > MyController.countSecondColor)
                    res += "The first player won."
                else if(MyController.countFirstColor < MyController.countSecondColor)
                    res += "The second player won."
                else
                    res += "Tied!"
                return res;
            }

            onAccepted: {
                MyController.startGame();
            }
        }
        FileDialog
        {
            id: openFileDialog
//            visible: false
//            modality: Qt.WindowModal
//            selectMultiple: false
//            selectExisting: true
//            selectFolder: false
            nameFilters: [ "Font files (*.json)" ]
            title: qsTr("Select file")

            onAccepted:
            {
                var path = openFileDialog.fileUrl.toString();
                path = path.replace(/^(file:\/{3})/,""); //remove <file:///> from path
                console.log("open file accepted: You chose: " + path)

                MyController.loadGame(path);
            }
        }

        FileDialog {
              id: saveFileDialog
              title: qsTr("Select file")
//              selectMultiple: false
//              folder: shortcuts.home
              nameFilters: [ "Font files (*.json)" ]
              onAccepted: {
                  var path = saveFileDialog.fileUrl.toString();
                  path = path.replace(/^(file:\/{3})/,""); //remove <file:///> from path
                  console.log("save file accepted: You chose: " + path)

                  MyController.saveGameAs(path);
              }
              onRejected: {
                  console.log("saveFileDialog: Canceled")
              }
          }
        NewGameDialog
        {
            id: newGameWindow
            title: "New Game"
            onAccepted:
            {
                MyController.startGame();
            }
        }

        SettingsDialog
        {
            id:settingsWindow
            title: qsTr("Settings")
            onAccepted:
            {
                settings.highlighted = false;
                MyController.startGame();
            }
        }

    }

    MessageDialog{
        id: dialogAbout
        title: "About"
        text: "Author: Alexandra Shestova
Year of release of the game: 2019"
        onAccepted: {
            visible = false;
        }
    }

}
