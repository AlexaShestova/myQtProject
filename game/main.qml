import QtQuick 2.8
//import QtQuick.Window 2.2
import QtQuick.Controls 1.4//2.0//1.4
//import MyData 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 720
    title: qsTr("My Game")
    Component.onCompleted: {
        //console.log(MyData.size)
    }

    menuBar: MenuBar {
              Menu {
                  title: "Game"
                  MenuItem { text: "newGame" }
                  MenuItem { text: "loadGame" }
              }

              Menu {
                  title: "Settings"
                  MenuItem { text: "Colors" }
                  MenuItem { text: "Players" }
              }
          }

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

        GridView {
            id: grid
            width: MyData.size * (root.widthRect + 20)
            height: MyData.size * (root.widthRect + 20)
//            baselineOffset: 5
            anchors.bottom: root.bottom
//            anchors.left: root.left
//            anchors.right: root.right
//            anchors.verticalCenter: root.verticalCenter
            anchors.horizontalCenter: root.horizontalCenter
            property bool isFirstPlayer: true

            delegate: Rectangle {
                id: rectDelegate
                Behavior on color {
                    SequentialAnimation {

                        PauseAnimation {
                            duration: 500//Delay
                        }
                        ColorAnimation {
                            duration: 2000
                        }
                    }


                }
                x: {
//                    console.log(index + "/ " + MyData.size + "=" + Math.floor(index/ MyData.size ))
                    return Math.floor((index / MyData.size)) * width + 20
                }
                y: (index % MyData.size) * width
                width: root.widthRect//root.width / model.count
                height: root.widthRect
                color: ColorData
                Text {
                    font.pointSize: 30
                    anchors.centerIn: parent
                    text: IntData
                }

            }

            model:  /*ListView {
            model:*/
                    MyData
            //        }


            MouseArea {
                id: mouseArea
                anchors.fill: parent

                onClicked: {
                    console.log("onClicked : (" + mouseX + " : " + mouseY + ") : index = " + grid.indexAt(mouseX,mouseY))
                    console.log("check = " + MyData.checkRect(grid.indexAt(mouseX,mouseY), grid.isFirstPlayer))
                    if(MyData.checkRect(grid.indexAt(mouseX,mouseY), grid.isFirstPlayer))
                    {
//                        grid.itemAt(mouseX,mouseY).color = "black"
                        MyData.process(grid.indexAt(mouseX,mouseY), grid.isFirstPlayer);
                        grid.isFirstPlayer = !grid.isFirstPlayer;
//                        MyData.beginResetModel();
//                        grid.itemAt(mouseX,mouseY).update()

//                        MyData.
                    }
                }
            }
        }
    }
}
