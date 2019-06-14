import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

LineSeries {
    capStyle: Qt.SquareCap
    pointLabelsVisible: true
    pointLabelsFont: Qt.font({pointSize: 11})
    pointLabelsFormat: "@yPoint"
    pointLabelsClipping: false
}
