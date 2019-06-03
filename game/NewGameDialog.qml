import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

Window
{
    id: newGameRoot

    width: 250
    height: 150

    modality: Qt.ApplicationModal
//    flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.WindowCloseButtonHint | Qt.WindowSystemMenuHint | Qt.MSWindowsFixedSizeDialogHint
    property int fontPointSize : 10
    property string fontFamily : "Arial"
    property int marginValue : 20

    signal accepted()

    Button
    {
        id: buttonOnePlayer
        width: 80
        anchors.left: parent.left
        anchors.leftMargin: newGameRoot.marginValue
        anchors.top: parent.top
        anchors.topMargin: newGameRoot.marginValue

        Label
        {
            anchors.fill: parent
            text: qsTr("One Player")
            font.pointSize: newGameRoot.fontPointSize
            font.family: newGameRoot.fontFamily
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onClicked:
        {
            MyController.numberPlayers = 1;
            newGameRoot.accepted();
            newGameRoot.visible = false;
        }
    }

    Button
    {
        id: buttonTwoPlayer
        width: 80
        anchors.right: parent.right
        anchors.rightMargin: newGameRoot.marginValue
        anchors.top: parent.top
        anchors.topMargin: newGameRoot.marginValue

        Label
        {
            anchors.fill: parent
            text: qsTr("Two Player")
            font.pointSize: newGameRoot.fontPointSize
            font.family: newGameRoot.fontFamily
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onClicked:
        {
            MyController.numberPlayers = 2;
            newGameRoot.accepted();
            newGameRoot.visible = false;
        }
    }
//    Button
//    {
//        id: buttonThreePlayer
//        width: 80
//        anchors.left: parent.left
//        anchors.leftMargin: newGameRoot.marginValue
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: newGameRoot.marginValue

//        Label
//        {
//            anchors.fill: parent
//            text: qsTr("Three Player")
//            font.pointSize: newGameRoot.fontPointSize
//            font.family: newGameRoot.fontFamily
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//        }

//        onClicked:
//        {
//            MyController.numberPlayers = 3;
//            newGameRoot.accepted();
//            newGameRoot.visible = false;
//        }
//    }
//    Button
//    {
//        id: buttonFourPlayer
//        width: 80
//        anchors.right: parent.right
//        anchors.rightMargin: newGameRoot.marginValue
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: newGameRoot.marginValue

//        Label
//        {
//            anchors.fill: parent
//            text: qsTr("Four Player")
//            font.pointSize: newGameRoot.fontPointSize
//            font.family: newGameRoot.fontFamily
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//        }

//        onClicked:
//        {
//            MyController.numberPlayers = 4;
//            newGameRoot.accepted();
//            newGameRoot.visible = false;
//        }
//    }
}
