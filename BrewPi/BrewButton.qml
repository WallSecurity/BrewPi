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
    id: btn
    text: qsTr("Rezept laden")
    anchors.centerIn: parent
    font.pointSize: 26
    contentItem: Text {
        text: btn.text
        color: Material.color(Material.Indigo, 2)
        font.pointSize: 26
    }
}
