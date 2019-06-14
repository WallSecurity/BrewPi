import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Controls.Material 2.3

SpinBox {
    id: sb
    from: 0
    to: 180
    stepSize: 1
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: parent.height / 4
    anchors.leftMargin: parent.width * 1/3
    scale: 1.35

    Text {
        text: "Dauer [min]"
        font.pointSize: 12
        color: Material.color(Material.Indigo, 2)
        anchors.right: parent.left
        anchors.rightMargin: parent.width / 8
        anchors.verticalCenter: sb.verticalCenter
    }

    Button {
        anchors.left: sb.right
        anchors.leftMargin: parent.width / 10
        contentItem: Label {
            text: "90 min"
            color: Material.color(Material.Indigo, 2)
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
        }
        onClicked: sb.value = 90
    }
}
