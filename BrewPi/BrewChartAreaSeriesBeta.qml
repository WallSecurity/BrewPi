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
    color: "#FF9900"
    opacity: 0.2
    borderColor: "transparent"
    lowerSeries: LineSeries {
        XYPoint { x: 0; y: 70 }
        XYPoint { x: 1000; y: 70 }
    }
    upperSeries: LineSeries {
        XYPoint { x: 0; y: 75 }
        XYPoint { x: 1000; y: 75 }
    }
}

