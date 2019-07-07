import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

AreaSeries {
    color: "#00FF00"
    opacity: 0.15
    borderColor: "transparent"
    lowerSeries: LineSeries {
        XYPoint { x: 0; y: 60 }
        XYPoint { x: 1000; y: 60 }
    }
    upperSeries: LineSeries {
        XYPoint { x: 0; y: 66 }
        XYPoint { x: 1000; y: 66 }
    }
}
