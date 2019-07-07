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
    color: "transparent"
    border.color: Material.color(Material.Indigo, 2)
    width: parent.width
    height: parent.height / 10
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: parent.height / 6.5
    radius: 4
}
