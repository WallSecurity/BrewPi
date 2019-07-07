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
    font.pointSize: 16
    color: Material.color(Material.Grey, 4)
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.topMargin: parent.height * 7/12
    anchors.leftMargin: parent.width / 15
    text: "Nächster Schritt:"
}
