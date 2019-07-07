import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

ChartView {
    width: parent.width / 2
    height: parent.height / 2
    anchors.top: parent.top
    theme: ChartView.ChartThemeQt
    legend.visible: false
    titleFont: Qt.font({pointSize: 14})
    antialiasing: true
    visible: false
}
