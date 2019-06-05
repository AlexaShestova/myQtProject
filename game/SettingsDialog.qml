import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.3

Window
{
    id: settingsRoot

    width: 300
    height: 530

    modality: Qt.ApplicationModal
    flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.WindowCloseButtonHint | Qt.WindowSystemMenuHint | Qt.MSWindowsFixedSizeDialogHint

    property int fontPointSize : 10
    property string fontFamily : "Arial"
    property int marginValue : 20

    signal accepted()

    function updateSettings()
    {
        var settings = MyController.getSettings();
        if( "Colors" in settings )
        {
            if( "numberColors" in settings["Colors"] )
            {
                spinBoxCountColor.value = settings["Colors"]["numberColors"];
            }

            if( "firstColor" in settings )
            {
                firstPlayerColor.currentIndex = firstPlayerColor.find( settings["Colors"]["firstColor"] );
            }

            if( "secondColor" in settings )
            {
                secondPlayerColor.currentIndex = secondPlayerColor.find( settings["Colors"]["secondColor"] );
            }

        }
    }

    GroupBox
    {
        id: groupBoxPlayingField

        width: parent.width - 2 * settingsRoot.marginValue
        height: 190

        anchors.top: parent.top
        anchors.topMargin: settingsRoot.marginValue
        anchors.left: parent.left
        anchors.leftMargin: settingsRoot.marginValue
        anchors.right: parent.right
        anchors.rightMargin: settingsRoot.marginValue
        title: qsTr("Playing field")

        Label
        {
            id: labelCountColors

            anchors.left: parent.left
            anchors.top: parent.top

            text: qsTr("Count Colors:")
            anchors.topMargin: settingsRoot.marginValue / 2
            anchors.leftMargin: settingsRoot.marginValue / 2
        }

        SpinBox
        {
            id: spinBoxCountColor
            width: 55
            anchors.right: parent.right
            anchors.rightMargin: settingsRoot.marginValue / 2

            anchors.verticalCenter: labelCountColors.verticalCenter

            value: 6 // MyController.m_numberColors
            minimumValue: 2
            maximumValue: 11
        }

        Label
        {
            id: labelFirstPlayerColor

            anchors.left: parent.left
            anchors.top: spinBoxCountColor.bottom

            text: qsTr("First player color:")
            anchors.topMargin: settingsRoot.marginValue / 2
            anchors.leftMargin: settingsRoot.marginValue / 2
        }
        ComboBox
        {
            id: firstPlayerColor
            anchors.right: parent.right
            anchors.rightMargin: settingsRoot.marginValue / 2
            anchors.leftMargin: settingsRoot.marginValue / 2
            anchors.topMargin: settingsRoot.marginValue / 2

            anchors.left: parent.left
            anchors.top: labelFirstPlayerColor.bottom

            model: MyController.getAllColors(1)
        }
        //second player color
        Label
        {
            id: labelSecondPlayerColor

            anchors.left: parent.left
            anchors.top: firstPlayerColor.bottom

            text: qsTr("Second player color:")
            anchors.topMargin: settingsRoot.marginValue / 2
            anchors.leftMargin: settingsRoot.marginValue / 2
        }
        ComboBox
        {
            id: secondPlayerColor
            anchors.right: parent.right
            anchors.rightMargin: settingsRoot.marginValue / 2
            anchors.leftMargin: settingsRoot.marginValue / 2
            anchors.topMargin: settingsRoot.marginValue / 2

            anchors.left: parent.left
            anchors.top: labelSecondPlayerColor.bottom

            model: MyController.getAllColors(2)
        }

    }

    Button
    {
        id: buttonOk
        width: 80
        anchors.left: parent.left
        anchors.leftMargin: settingsRoot.marginValue
        anchors.bottom: parent.bottom
        anchors.bottomMargin: settingsRoot.marginValue

        Label
        {
            anchors.fill: parent
            text: qsTr("OK")
            font.pointSize: settingsRoot.fontPointSize
            font.family: settingsRoot.fontFamily
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onClicked:
        {
            if(firstPlayerColor.currentText == secondPlayerColor.currentText)
                messageDialog.visible = true;
            else
            {
                var settingsColor = {   "numberColors" : spinBoxCountColor.value,
                    "firstColor" : firstPlayerColor.currentText,
                    "secondColor" : secondPlayerColor.currentText};
                MyController.setSettings( "Colors", settingsColor );

                settingsRoot.visible = false;
                settingsRoot.accepted();
            }
        }
    }

    Button
    {
        id: buttonCancel
        width: buttonOk.width
        anchors.right: parent.right
        anchors.rightMargin: settingsRoot.marginValue
        anchors.bottom: parent.bottom
        anchors.bottomMargin: settingsRoot.marginValue

        Label
        {
            anchors.fill: parent
            text: qsTr("Cancel")
            font.pointSize: settingsRoot.fontPointSize
            font.family: settingsRoot.fontFamily
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onClicked: settingsRoot.visible = false
    }
    MessageDialog
    {
        id: messageDialog
        icon: StandardIcon.Critical
        title: "Warning"
        text: "Choose a different color for the second player"
        onAccepted: {
            visible = false;
        }
        //        Component.onCompleted: visible = true
    }
}
