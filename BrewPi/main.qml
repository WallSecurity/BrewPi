import QtQuick 2.9
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Window 2.3

import brewpi.enum 1.0

ApplicationWindow {
    id: window
    visible: true
    //CHANGE ME
//    visibility: Qt.WindowFullScreen
    width: 1024
    height: 600
    title: qsTr("BrewPi")

    Connections {
        target: SensorData
        onTemperatureChanged: {
            console.log("adding point (", SensorData.getTimer(), ",",SensorData.temperatureToDouble(), ")");
            brewChartLineSeries.append(SensorData.getTimer(), SensorData.temperatureToDouble());
        }
    }

    function setUpEndScreen() {
        startButton.visible = false
        stopButton.visible = false
    }

    function setAutoMotorSpeed() {
        if (motorSwitch.checked == true) {
            SensorData.setAutoMotorSpeed(ProgressClass.name(0))
            speedSlider.value = SensorData.getSpeed()
        }
    }

    function setUpProgressTimer() {
        if (ProgressClass.temperature(0) >= 0) {
            brewProgress.value = 0
            brewProgress.to = ProgressClass.duration(0)
            brewTargetTemp.text = ProgressClass.temperature(0)
            progressTitle.text = ProgressClass.name(0)
            brewProgressTotal.stop()
            brewProgressTotal.interval = ProgressClass.duration(0) * 60000
            setAutoMotorSpeed()
            brewProgressTotal.start()
        } else {
            brewDurationRem.text = "0 Minuten"
            stopButton.visible = false
            startButton.visible = true
            swipeView.interactive = true
            tabBar.enabled = true
            brewProgressTimer.stop()
            brewTempTimer.stop()
            brewProgressTotal.stop()
            brewDurationTimer.stop()
            SensorData.endBrewProcess()
            SensorData.setMotorSpeed(0)
            speedSlider.value = SensorData.getSpeed()
            setUpEndScreen()
        }
    }

    function setUpNextProgress() {
        if (ProgressClass.nextTemperature(0) >= 0) {
            brewProgressNext.to = ProgressClass.nextDuration(0)
            progressTitleNextStep.text = ProgressClass.nextName(0)
        } else {
            progressTitleNext.visible = false
            progressTitleNextStep.visible = false
            brewProgressNext.visible = false
        }
    }

    function checkTargetReachedOnChanged() {
        if (ProgressClass.isHeatPhase(0)) {
            if (Number(brewCurrentTemp.text) >= Number(brewTargetTemp.text)) {
                brewDurationTotal.text = Math.round((Number(brewDurationTotal.text) - (ProgressClass.duration(0) * (1 - brewProgress.value)))*100)/100
                brewDurationRem.text = Math.round((Number(brewDurationRem.text) - (ProgressClass.duration(0) * (1 - brewProgress.value)))*100)/100
                ProgressClass.removeFirst()
                setUpProgressTimer()
                setUpNextProgress()
            }
        }
    }

    function repeatUntilTargetReached() {
        if (ProgressClass.isHeatPhase(0)) {
            brewDurationTotal.text = Math.round((Number(brewDurationTotal.text) + ProgressClass.duration(0))*100)/100
            brewDurationRem.text = Math.round((Number(brewDurationRem.text) + ProgressClass.duration(0))*100)/100
            setUpProgressTimer()
            setUpNextProgress()
        } else {
            ProgressClass.removeFirst()
            setUpProgressTimer()
            setUpNextProgress()
        }
    }

    TabBar {
        id: tabBar
        spacing: 1
        width: parent.width
        height: implicitHeight
        currentIndex: swipeView.currentIndex


        TabButton {
            id: mashButton
            text: "Maischen"
            font.pixelSize: 30
            height: implicitHeight
        }

        TabButton {
            id: boilButton
            text: "Kochen"
            font.pixelSize: 30
            height: implicitHeight
        }

        TabButton {
            id: recipeButton
            text: "Rezepte"
            font.pixelSize: 30
            height: implicitHeight
        }

        TabButton {
            id: settingsButton
            text: "Optionen"
            font.pixelSize: 30
            height: implicitHeight
        }

    }

    SwipeView {
        id: swipeView
        width: window.width
        height: window.height - tabBar.height
        anchors.top: tabBar.bottom
        anchors.left: window.left
        currentIndex: tabBar.currentIndex
        clip: true

        Item {
            id: brewPage
            width: window.width
            height: window.height - tabBar.height

            BrewButton {
                id: welcome
                onClicked: swipeView.setCurrentIndex(2)
            }

            Rectangle {
                id: brewTitleRect
                color: "transparent"
                width: brewPage.width / 2
                height: brewPage.height / 10
                anchors.top: brewPage.top
                anchors.right: brewPage.right

                BrewTitle {
                    id: brewTitle
                }
            }

            BrewChartView {
                id: brewChartView

                BrewChartLineSeries {
                    id: recipeChartLineSeries
                    axisX: axisX
                    axisY: axisY
                    color: "saddlebrown"
                    width: 2
                }

                BrewChartLineSeries {
                    id: brewChartLineSeries
                    color: "red"
                    width: 0.5
                    pointLabelsVisible: false
                }

                BrewChartAxisX {
                    id: axisX
                }
                BrewChartAxisY {
                    id: axisY
                }

                BrewChartAreaSeriesFerula {
                    id: brewChartAreaSeriesFerula
                }
                BrewChartAreaSeriesProtease {
                    id: brewChartAreaSeriesProtease
                }
                BrewChartAreaSeriesAlpha {
                    id: brewChartAreaSeriesAlpha
                }
                BrewChartAreaSeriesBeta {
                    id: brewChartAreaSeriesBeta
                }
            }

            Rectangle {
                id: progressRect
                visible: false
                color: "transparent"
                width: brewPage.width * 1/3
                height: brewPage.height / 2
                anchors.left: brewPage.left
                anchors.bottom: brewPage.bottom

                BrewProgressTitle {
                    id: progressTitle
                }

                BrewProgressBar {
                    id: brewProgress

                    BrewProgressTimer {
                        id: brewProgressTimer
                        onTriggered: brewProgress.value <= brewProgress.to ? brewProgress.value += 1/600 : brewProgressTimer.stop()
                    }

                    BrewProgressTotalTimer {
                        id: brewProgressTotal
                        onTriggered: repeatUntilTargetReached()
                    }
                }

                BrewProgressTitleNext {
                    id: progressTitleNext
                }

                BrewProgressTitleNextStep {
                    id: progressTitleNextStep
                }

                BrewProgressBarNext {
                    id: brewProgressNext
                }

                BrewSeparatorNext {
                    id: stepSeparator
                }

                BrewSeparator {
                    id: progressSeparator
                }
            }

            Rectangle {
                id: infoRect
                visible: false
                color: "transparent"
                width: brewPage.width * 1/3
                height: brewPage.height / 2
                anchors.left: brewPage.left
                anchors.leftMargin: progressRect.width + progressSeparator.width
                anchors.bottom: brewPage.bottom

                BrewDurationComplete {
                    id: brewDurationTotal

                    BrewDurationTimer {
                        id: brewDurationTimer
                        onTriggered: {
                            brewDurationRem.text = Math.round((Number(brewDurationRem.text) - 1)*100) / 100
                        }
                    }

                    BrewDurationRemaining {
                        id: brewDurationRem
                    }
                }

                BrewTemperatureCurrent {
                    id: brewCurrentTemp
                    color: (Number(brewCurrentTemp.text) <= Number(brewTargetTemp.text) - 3) || (Number(brewCurrentTemp.text) >= Number(brewTargetTemp.text) + 3) ? Material.color(Material.Red, 8) : Material.color(Material.Green, 8)
                    onTextChanged: checkTargetReachedOnChanged()

                    BrewTemperatureTimer {
                        id: brewTempTimer
                        onTriggered: {
                            brewCurrentTemp.text = SensorData.temperature()
                            console.log("Temperature: ", SensorData.temperature());
                        }
                    }
                    BrewTemperatureTarget {
                        id: brewTargetTemp
                    }
                }


            }

            Rectangle {
                id: controlRect
                color: "transparent"
                visible: false
                width: (brewPage.width / 2) - 10
                height: brewPage.height
                anchors.top: brewPage.top
                anchors.left: brewPage.left
                anchors.leftMargin: brewPage.width / 2

                BrewMotorRect {
                    id: motorRect

                    BrewMotorTitle {
                        id: motorTitle
                    }

                    Switch {
                        id: motorSwitch
                        checked: true
                        text: motorSwitch.checked ? "Auto" : "Manuell"
                        onCheckedChanged: setAutoMotorSpeed()
                    }

                    BrewMotorSpeedSlider {
                        id: speedSlider
                        enabled: motorSwitch.checked ? false : true
                        onValueChanged: SensorData.setMotorSpeed(speedSlider.value);
                    }
                }

                BrewStartButton {
                    id: startButton
                    onClicked: {
                        SensorData.endIntervall()
                        stopButton.visible = true
                        startButton.visible = false
                        swipeView.interactive = false
                        tabBar.enabled = false
                        brewProgressTimer.start()
                        brewProgressTotal.start()
                        brewTempTimer.start()
                        brewDurationTimer.start()
                        SensorData.setupTimers(RecipeGraph.getData(Enum.BrewDura))
                        setAutoMotorSpeed()
                    }
                }
                BrewStopButton {
                    id: stopButton
                    onClicked: {
                        stopButton.visible = false
                        startButton.visible = true
                        progressRect.visible = false
                        controlRect.visible = false
                        infoRect.visible = false
                        brewChartView.visible = false
                        brewTitle.visible = false
                        welcome.visible = true
                        swipeView.interactive = true
                        tabBar.enabled = true
                        brewProgressTimer.stop()
                        brewTempTimer.stop()
                        brewProgressTotal.stop()
                        brewDurationTimer.stop()
                        brewProgress.value = 0
                        SensorData.setMotorSpeed(0)
                        speedSlider.value = SensorData.getSpeed()
                        SensorData.endBrewProcess()
                    }
                }
            }
        }

        Item {
            id: cookPage
            width: window.width
            height: window.height - tabBar.height

            CookLeftTwoThird {
                id: leftHalth

                CookTargetTempSpinBox {
                    id: targetTempSpinBox
                }

                CookTargetDuraSpinBox {
                    id: targetDuraSpinBox
                    onValueChanged: {
                        cookDuraTotal.text = targetDuraSpinBox.value == 1?  targetDuraSpinBox.value + " Minute" : targetDuraSpinBox.value + " Minuten"
                        cookDuraRem.text = targetDuraSpinBox.value == 1?  targetDuraSpinBox.value + " Minute" : targetDuraSpinBox.value + " Minuten"
                        cookProgressBar.to = targetDuraSpinBox.value
                    }
                }

                BrewMotorRect {
                    id: cookMotorRect
                    anchors.topMargin: parent.height / 2
                    anchors.leftMargin: parent.width / 15
                    width: parent.width * 9.15/12

                    BrewMotorTitle {
                        id: cookMotorTitle
                    }

                    Switch {
                        id: cookMotorSwitch
                        checked: true
                        text: cookMotorSwitch.checked ? "Auto" : "Manuell"
                    }

                    BrewMotorSpeedSlider {
                        id: cookSpeedSlider
                        enabled: cookMotorSwitch.checked ? false : true
                        onValueChanged: SensorData.setMotorSpeed(cookSpeedSlider.value);
                    }
                }
            }


            CookRightOneThird {
                id: rightHalth

                BrewProgressBar {
                    id: cookProgressBar
                    anchors.leftMargin: 0
                    to: 0
                }

                BrewTemperatureCurrent {
                    id: cookTempCurrent
                    color: (Number(cookTempCurrent.text) <= Number(targetTempSpinBox.value) - 3) || (Number(cookTempCurrent.text) >= Number(targetTempSpinBox.value) + 3) ? Material.color(Material.Red, 8) : Material.color(Material.Green, 8)
                    anchors.leftMargin: 0
                    anchors.topMargin: parent.height / 7.5
                }

                BrewDurationComplete {
                    id: cookDuraTotal
                    anchors.leftMargin: parent.width * 4.8/12
                    anchors.topMargin: parent.height * 5/12
                    text: "0 Minuten"

                    BrewDurationRemaining {
                        id: cookDuraRem
                        text: "0 Minuten"
                    }
                }

                BrewStartButton {
                    id: cookStartButton
                    width: parent.width / 3
                    height: parent.height / 9
                    onClicked: {
                        cookStopButton.visible = true
                        cookStartButton.visible = false
                        swipeView.interactive = false
                        tabBar.enabled = false
                    }
                }
                BrewStopButton {
                    id: cookStopButton
                    width: parent.width / 3
                    height: parent.height / 9
                    onClicked: {
                        cookStartButton.visible = true
                        cookStopButton.visible = false
                        swipeView.interactive = true
                        tabBar.enabled = true
                        SensorData.setMotorSpeed(0)
                        cookSpeedSlider.value = SensorData.getSpeed()
                    }
                }
            }
        }

        Item {
            id: recipePage
            width: window.width
            height: window.height - tabBar.height
            RecipeForm {
                id: recipeForm
                onRecipeLoaded: {
                    recipeChartLineSeries.clear();
                    for(var i = 0; i < RecipeGraph.getSize(); i++) {
                        recipeChartLineSeries.append(RecipeGraph.getX(i), RecipeGraph.getY(i));
                        //                        console.log("adding point (", RecipeGraph.getX(i), ",",RecipeGraph.getY(i), ")");
                    }
                    axisX.max = RecipeGraph.getTotalX() + 5
                    axisY.min = RecipeGraph.getMinY() - 4
                    axisY.max = RecipeGraph.getMaxY() + 4
                    welcome.visible = false
                    brewDurationTotal.text = Math.round(RecipeGraph.getData(Enum.BrewDura)*100) / 100
                    brewDurationRem.text = brewDurationTotal.text
                    brewProgress.to = ProgressClass.duration(0)
                    brewTargetTemp.text = ProgressClass.temperature(0)
                    progressTitle.text = ProgressClass.name(0)
                    brewProgressTotal.interval = ProgressClass.duration(0) * 60000
                    brewTitle.text = RecipeGraph.getData(Enum.Name) + "   v. " + RecipeGraph.getData(Enum.Number)
                    progressRect.visible = true
                    controlRect.visible = true
                    infoRect.visible = true
                    brewChartView.visible = true
                    brewTitle.visible = true
                    SensorData.setIntervall()
                    brewTempTimer.start()
                    setUpNextProgress()
                    swipeView.setCurrentIndex(0)
                }
            }
        }


        Item {
            id: settingPage
            width: window.width
            height: window.height - tabBar.height

            SettingForm {
                id: settingForm
            }
        }
    }
}
