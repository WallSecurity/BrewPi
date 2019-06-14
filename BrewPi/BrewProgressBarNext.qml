import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

ProgressBar {
    id: pBar
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.topMargin: parent.height * 5/6
    anchors.leftMargin: parent.width / 15
    indeterminate: true
    z: 2
    background: Rectangle {
        implicitWidth: 300
        implicitHeight: 15
        radius: 4
        color: Material.color(Material.Grey, 5)
    }
    contentItem: Item {
        implicitWidth: 300
        implicitHeight: 14

        Rectangle {
            width: pBar.visualPosition * parent.width
            height: parent.height
            color: Material.color(Material.Grey, 5)
            radius: 4
        }
    }

    Text {
        color: Material.color(Material.Grey, 5)
        font.pointSize: 12
        anchors.bottom: pBar.top
        anchors.bottomMargin: 4
        anchors.right: pBar.right
        text: Math.round(pBar.to*10) / 10 + " [min]"
    }
}
