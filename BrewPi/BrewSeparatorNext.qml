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
    color: Material.color(Material.Indigo, 2)
    width: parent.width * 4/5
    radius: 3
    height: 2
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: parent.height / 2
    anchors.leftMargin: parent.width * 1/10
}
