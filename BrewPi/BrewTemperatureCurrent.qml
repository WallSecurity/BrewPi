import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

Text {
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: parent.height * 5/10
    anchors.leftMargin: parent.width / 10
    font.pointSize: 16
    text: "00.00"

    Text {
        text: qsTr("Temperatur")
        anchors.bottom: parent.top
        font.pointSize: 16
        color: Material.color(Material.Indigo, 2)
    }

    Text {
        text: qsTr(" °C")
        anchors.left: parent.right
        font.pointSize: 16
        color: parent.color
    }
}
