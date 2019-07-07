import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

Rectangle {
    id: backGround
    color: "transparent"
    height: parent.height
    width: parent.width
    anchors.top: parent.top
    anchors.left: parent.left

    property int inputWidth: 50

    Rectangle {
        id: settingRect
        color: "transparent"
        height: parent.height * 4/5
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        RowLayout {
            id: rowLayout
            height: parent.height
            width: parent.width

            GridLayout {
                id: leftGrid
                columns: 2
                columnSpacing: 20
                rowSpacing: 20
                width: parent.width / 2
                height: parent.height
                Layout.alignment: Qt.AlignTop
                Layout.leftMargin: parent.width / 20
                Layout.topMargin: parent.height / 20

                Text {id: port; text: "Arduino USB Port:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: portF; implicitWidth: inputWidth;text: Globals.comportNumber(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: tempIntF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 37}}

                Text {id: tempInt; text: "Temperatur-Intervall [sec]:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: tempIntF; implicitWidth: inputWidth; text: Globals.intervallTimer(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: speedNormF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: speedNorm; text: "Motor-Geschwindigkeit normal [%]:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: speedNormF; implicitWidth: inputWidth; text: Globals.motorspeedNormal(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: speedHeatF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: speedHeat; text: "Motor-Geschwindigkeit heizen [%]:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: speedHeatF; implicitWidth: inputWidth; text: Globals.motorspeedHeat(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: focus = false; onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}
            }

            GridLayout {
                id: rightGrid
                columns: 2
                columnSpacing: 20
                rowSpacing: 20
                width: parent.width / 2
                height: parent.height
                Layout.alignment: Qt.AlignTop
                Layout.leftMargin: parent.height / 20
                Layout.topMargin: parent.height / 20

                Text {id: title; text: "Heiz-Multiplikatoren [Min pro 1°C]"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                Text {id: empty; text: ""; font.pointSize: 16}

                Text {id: sfMult; text: "Einmaischen -> Weizen-Rast:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: sfMultF; implicitWidth: inputWidth; text: Globals.heatingMultiplierStartFerula(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: fpMultF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: fpMult; text: "Weizen-Rast -> Protease-Rast:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: fpMultF; implicitWidth: inputWidth; text: Globals.heatingMultiplierFerulaProtease(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: pmMultF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: pmMult; text: "Protease-Rast -> Maltose-Rast:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: pmMultF; implicitWidth: inputWidth; text: Globals.heatingMultiplierProteaseMaltose(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: msMultF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: msMult; text: "Maltose-Rast -> Zucker-Rast:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: msMultF; implicitWidth: inputWidth; text: Globals.heatingMultiplierMaltoseSugar(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: seMultF.forceActiveFocus(); onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}

                Text {id: seMult; text: "Zucker-Rast -> Abmaischen:"; font.pointSize: 16; color: Material.color(Material.Indigo, 2)}
                TextField {id: seMultF; implicitWidth: inputWidth; text: Globals.heatingMultiplierSugarEnd(); horizontalAlignment: TextInput.AlignHCenter; verticalAlignment: TextInput.AlignBottom; font.pointSize: 14; selectByMouse: true; persistentSelection: false; onAccepted: focus = false; onAcceptableInputChanged: saveButton.enabled = acceptableInput; validator: IntValidator {bottom: 0; top: 100}}
            }
        }
    }
    Rectangle {
        id: buttonRect
        color: "transparent"
        height: parent.height * 1/5
        width: parent.width
        anchors.top: settingRect.bottom
        anchors.left: settingRect.left

        Timer {
            id: saveTimer
            interval: 2000
            repeat: false
            onTriggered: {
                saveButton.Material.background = Material.color(Material.Grey, 7)
                saveButton.text = "Speichern"
            }
        }

        Button {
            id: saveButton
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: parent.height / 10
            anchors.rightMargin: parent.width / 20
            text: "Speichern"
            font.pointSize: 16
            height: parent.height / 1.5
            width: parent.width / 6
            onClicked: {
                Globals.setComportNumber(portF.text)
                Globals.setIntervallTimer(tempIntF.text)
                Globals.setMotorspeedNormal(speedNormF.text)
                Globals.setMotorspeedHeat(speedHeatF.text)
                Globals.setHeatingMultiplierStartFerula(sfMultF.text)
                Globals.setHeatingMultiplierFerulaProtease(fpMultF.text)
                Globals.setHeatingMultiplierProteaseMaltose(pmMultF.text)
                Globals.setHeatingMultiplierMaltoseSugar(msMultF.text)
                Globals.setHeatingMultiplierSugarEnd(seMultF.text)
                Globals.saveSettingsToFile()
                saveTimer.start()
                Material.background = Material.color(Material.Green, 4)
                text = "Gespeichert"
            }
        }
    }
}
