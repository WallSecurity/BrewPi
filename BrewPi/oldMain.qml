import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQml 2.3
import QtCharts 2.3

ApplicationWindow {
    id: app
    visible: true
    width: 800
    height: 480
    title: qsTr("BrewPi")

    Loader {
        id: loader
    }

    Rectangle {
        id: controlBarBackground
        width: app.width
        height: 50
        anchors.top: app.top
        anchors.left: app.left
        color: Material.color(Material.Grey, 8)

        Rectangle {
            id: controlBar
            width: controlBarBackground.width - 10
            height: 50
            anchors.top: app.top
            anchors.left: app.left
            x: 5
            color: Material.color(Material.Grey, 8)

            RowLayout {
                spacing: 2
                anchors.fill: controlBar
                Layout.maximumWidth: 780
                Button {
                    id: mainPage
                    Layout.maximumWidth: 265
                    Layout.maximumHeight: 60
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "Brauerei"
                }
                Button {
                    id: recipePage
                    Layout.maximumWidth: 265
                    Layout.maximumHeight: 60
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //            anchors.left: mainPage.right
                    text: "Rezepte"
                }
                Button {
                    id: settingPage
                    Layout.maximumWidth: 265
                    Layout.maximumHeight: 60
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //            anchors.left: recipePage.right
                    text: "Einstellungen"
                }
            }
        }
    }

    Rectangle {
        id: mainLayout
        width: parent.width
        height: 430
        anchors.top: controlBarBackground.top
        anchors.left: controlBarBackground.left
        color: "transparent"

        //chart
        ChartView {
            id: lineView
            width: mainLayout.width * 5/10
            height: mainLayout.height *3/5
            anchors.top: mainLayout.top
            anchors.left: mainLayout.left
            anchors.topMargin: 60
            theme: ChartView.ChartThemeQt
            legend.visible: false
            titleFont: Qt.font({pointSize: 14})
            title: RecipeGraph.getName() + " " + RecipeGraph.getNumber()
            antialiasing: true

            ValueAxis {
                id: axisX
                min: 0
                max: RecipeGraph.getTotalX() + 10
                labelsFont: Qt.font({pointSize: 12})
                tickCount: 2
            }

            ValueAxis {
                id: axisY
                min: 0 //RecipeGraph.getMinY() - 5
                max: RecipeGraph.getMaxY() + 2
                labelsFont: Qt.font({pointSize: 12})
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                //            onWheel: {
                //                if (wheel.angleDelta.y > 0) {
                //                    lineView.zoomIn()
                //                    accepted: true
                //                }
                //                else {
                //                    lineView.zoomOut()
                //                    accepted: true
                //                }
                //            }
            }

            AreaSeries {
                id: glucanase
                axisX: axisX
                axisY: axisY
                color: "#CCCCCC"
                opacity: 0.45
                borderColor: "transparent"
                lowerSeries: LineSeries {
                    XYPoint { x: 0; y: 35 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 35 }
                }
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 39 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 39 }
                }
            }

            AreaSeries{
                id: ferula
                color: "#00FFFF"
                opacity: 0.2
                borderColor: "transparent"
                lowerSeries: LineSeries {
                    XYPoint { x: 0; y: 44 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 44 }
                }
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 46 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 46 }
                }
            }

            AreaSeries {
                id: protease
                color: "#FFFF00"
                opacity: 0.2
                borderColor: "transparent"
                lowerSeries: LineSeries {
                    XYPoint { x: 0; y: 50 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 50 }
                }
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 56 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 56 }
                }
            }

            AreaSeries {
                id: alpha
                color: "#00FF00"
                opacity: 0.15
                borderColor: "transparent"
                lowerSeries: LineSeries {
                    XYPoint { x: 0; y: 60 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 60 }
                }
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 66 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 66 }
                }
            }

            AreaSeries {
                id: beta
                color: "#FF9900"
                opacity: 0.2
                borderColor: "transparent"
                lowerSeries: LineSeries {
                    XYPoint { x: 0; y: 70 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 70 }
                }
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 75 }
                    XYPoint { x: RecipeGraph.getTotalX() + 10; y: 75 }
                }
            }

            LineSeries {
                id: recipeSeries
                capStyle: Qt.SquareCap
                pointLabelsVisible: true
                pointLabelsFont: Qt.font({pointSize: 11})
                pointLabelsFormat: "@yPoint"
                pointLabelsClipping: false
                Component.onCompleted: {
                    for(var i = 0; i < RecipeGraph.getSize(); i++) {
                        recipeSeries.append(RecipeGraph.getX(i), RecipeGraph.getY(i));
                    }
                }
            }

            LineSeries {
                id: dataSeries
                capStyle: Qt.SquareCap
                pointLabelsVisible: false
                color: "red"

                function addPoint(x, y) {
                    dataSeries.append(x,y);
                }

            }
        }


        ProgressCircle {
            id: startMash
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Component.onCompleted: startMash.start()
        }

        //Buttons
        Button {
            id: start
            anchors.bottom: mainLayout.bottom
            anchors.right: mainLayout.right
            anchors.bottomMargin: 100
            anchors.rightMargin: 50
            text: "Start"
            onClicked: {
                //                TempData.startBrewProcess()
                //                recipeWindow.show()
                loader.source = "RecipeForm.qml"
                app.hide()
            }
        }

        Button {
            id: abort
            anchors.right: start.left
            anchors.bottom: start.bottom
            anchors.rightMargin: 50
            text: "Stop"
            onClicked: {
                TempData.endBrewProcess()
            }
        }

        Text {
            id: tempT
            width: 30
            anchors.top: mainLayout.top
            anchors.right: mainLayout.right
            anchors.topMargin: 100
            anchors.rightMargin: 50
            color: "white"
        }
        Timer {
            id: timer
            interval: 1000; running: true; repeat: true; triggeredOnStart: true
            onTriggered: {
                time.text = TempData.getTimer()
                tempT.text = TempData.temperature() + " °C"
            }
        }
        Timer {
            id: timerChart
            interval: 1000; running: true; repeat: true; triggeredOnStart: true
            onTriggered: {
                time.text = TempData.getTimer()
                tempT.text = TempData.temperature() + " °C"
            }
        }
        Text {
            id: time
            anchors.top: tempT.top
            anchors.right: tempT.left
            anchors.rightMargin: 50
            color: "white"
        }
    }
}
