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
    anchors.left: parent.left
    anchors.top: parent.bottom
    anchors.topMargin: 2
    font.pointSize: 16
    color: Material.color(Material.Indigo, 2)

    Text {
        anchors.right: parent.left
        font.pointSize: parent.font.pointSize
        color: parent.color
        text: "verbleibend: "
    }

    Text {
        anchors.left: parent.right
        font.pointSize: parent.font.pointSize
        color: parent.color
        text: " Minuten"
    }
}
