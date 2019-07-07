import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

Button {
    Material.background: Material.color(Material.Red, 8)
    text: "STOP"
    visible: false
    width: parent.width / 4.5
    height: parent.height / 9
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.bottomMargin: parent.height / 10
    anchors.rightMargin: parent.height / 10
}
