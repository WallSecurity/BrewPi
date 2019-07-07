import QtQuick 2.9
import QtQuick.Controls 1.6
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3
import QtQuick.Controls.Styles 1.4

Slider {
    id: slider
    minimumValue: 25
    maximumValue: 100
    stepSize: 5
    wheelEnabled: false
    tickmarksEnabled: false
    width: parent.width * 2/3
    height: parent.height
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.rightMargin: parent.width / 9

    Text {
        text: slider.value < 30 ? 0 + "%" : slider.value + "%"
        color: Material.color(Material.Indigo, 2)
        font.pointSize: 12
        anchors.left: slider.right
        anchors.verticalCenter: slider.verticalCenter
        anchors.leftMargin: 10
    }
}
