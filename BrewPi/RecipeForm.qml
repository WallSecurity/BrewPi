import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQuick.Window 2.3

import brewpi.recipemodel 1.0

ListView {
    id: recipeView
    width: parent.width
    height: parent.height
    headerPositioning: ListView.OverlayHeader
    clip: true
    property int itemCount: 10 //number of items displayed per view
    property int iconWidth: 35
    property int iconHeight: 35
    property int formButtonWidth: 200
    property int formButtonHeight : 60
    property int formButtonOffsetX : 300
    property int formButtonOffsetY : 400
    property int formButtonMargin : 20
    property int deleteButtonOffsetX : 0
    property int deleteButtonOffsetY: 150
    signal recipeLoaded
    spacing: 0

    model: BrewRecipeModel {
        list: RecipeList
    }

    //MsgDlg for removing recipes
    Window {
        id: deleteDialog
        title: "Rezept löschen?"
        width: 420
        height: 240
        flags: "Dialog"
        modality: Qt.WindowModal
        color: Material.color(Material.Grey, 9)

        Text {
            id: deleteText
            text: qsTr("Rezept löschen?")
            color: Material.color(Material.Indigo, 2)
            font.pointSize: 22
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -50
        }

        Button {
            id: deleteButton
            text: "Löschen"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: deleteButtonOffsetX
            y: deleteButtonOffsetY
            onClicked: {
                model.removeRow(currentIndex)
                deleteDialog.close()
            }
        }

        Button {
            id: noDeleteButton
            text: "Abbrechen"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: deleteButtonOffsetX
            y: deleteButtonOffsetY
            anchors.left: deleteButton.right
            anchors.leftMargin: formButtonMargin
            onClicked: deleteDialog.close()
        }
    }

    //Create new Recipe
    Window {
        id: createRecipeWindow
        width: 800
        height: 480
        flags: "Dialog"
        modality: Qt.WindowModal
        title: "Neues Rezept"
        color: Material.color(Material.Grey, 9)

        ScrollView {
            anchors.fill: parent
            clip: true

            Flickable {
                contentHeight: editRecipeWindow.height * 1.5
                width: parent.width

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"

        Button {
            id: yesButton
            text: "Rezept erstellen"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: formButtonOffsetX
            y: formButtonOffsetY
            onClicked: {
                model.insertRecipe(tfNumber.text, tfName.text, tfDate.text, tfAmount.text, tfStartT.text, tfStartD.text, tfFeruT.text,tfFeruD.text,tfProtT.text, tfProtD.text, tfMaltT.text,tfMaltD.text,tfSugT.text,tfSugD.text, tfEndT.text,tfEndD.text)
                createRecipeWindow.close()
            }
        }

        Button {
            id: cancelButton
            text: "Abbrechen"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: formButtonOffsetX
            y: formButtonOffsetY
            anchors.left: yesButton.right
            anchors.leftMargin: formButtonMargin
            onClicked: createRecipeWindow.close()
        }

        RowLayout {
            id: infoRow
            anchors.fill: parent
            spacing: 0

            ColumnLayout {
                id: stdInfo
                Layout.alignment: Qt.AlignTop
                spacing: 10
                Layout.topMargin: 20
                Layout.leftMargin: 20

                Text {id: tName; text: "Name"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfName; selectByMouse: true; implicitWidth: infoRow.width /4; text: "BIER_NAME"; font.pointSize: 14; Layout.leftMargin: tName.leftPadding}

                Text {id: tNumber; text: "Version"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfNumber; selectByMouse: true; text: "01"; inputMask: "99"; font.pointSize: 14; Layout.leftMargin: tNumber.leftPadding}

                Text {id: tDate; text: "Datum"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfDate; selectByMouse: true; text: new Date().toLocaleDateString(Qt.locale("de_DE"), "dd-MM-yyyy") ;font.pointSize: 14; Layout.leftMargin: tDate.leftPadding}

                Text {id: tAmount; text: "Menge [Liter]"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfAmount; selectByMouse: true; text: "60.0"; font.pointSize: 14; Layout.leftMargin: tDate.leftPadding}
            }
            GridLayout {
                Layout.alignment: Qt.AlignTop
                Layout.topMargin: 10
                columns: 3
                columnSpacing: 30
                rowSpacing: 13

                Text {id: tRest; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tTemp; text: "[°C]"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tbDura; text: "[Min]"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}

                Text {id: tStartT; text: "Einmaischen"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfStartT; selectByMouse: true; text: "45.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                TextField {id: tfStartD; selectByMouse: true; text: "10"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                //                Text {id: tGlucT; text: "Glukanase-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                //                TextField {id: tfGlucT; selectByMouse: true; placeholderText: "39.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                //                TextField {id: tfGlucD; selectByMouse: true; placeholderText: "15"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                Text {id: tFeruT; text: "Ferula-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfFeruT; selectByMouse: true; placeholderText: "45.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                TextField {id: tfFeruD; selectByMouse: true; placeholderText: "15"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                Text {id: tProtT; text: "Protease-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfProtT; selectByMouse: true; text: "52.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                TextField {id: tfProtD; selectByMouse: true; text: "20"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                Text {id: tMaltT; text: "Maltose-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfMaltT; selectByMouse: true; text: "63.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                TextField {id: tfMaltD; selectByMouse: true; text: "30"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                Text {id: tSugT; text: "Zucker-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfSugT; selectByMouse: true; text: "72.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                TextField {id: tfSugD; selectByMouse: true; text: "30"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}

                Text {id: tEndT; text: "Abmaischen"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                TextField {id: tfEndT; selectByMouse: true; text: "78.0"; font.pointSize: 14; Layout.leftMargin: tTemp.leftPadding}
                Text {id: tfEndD; text: "0"; color: "white"; font.pointSize: 14; Layout.leftMargin: tbDura.leftPadding}
            }
        }
                }
            }
        }
    }


    //edit Button
    Window {
        id: editRecipeWindow
        width: 800
        height: 480
        y: 0
        flags: "Dialog"
        modality: Qt.WindowModal
        title: "Rezept bearbeiten"
        color: Material.color(Material.Grey, 9)

        ScrollView {
            id: scrollView
            anchors.fill: parent
            clip: true

            Flickable {
                contentHeight: editRecipeWindow.height * 1.5
                width: parent.width

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"


                    Button {
                        id: yesButton2
                        text: "Rezept ändern"
                        font.pointSize: 15
                        width: formButtonWidth
                        height: formButtonHeight
                        x: formButtonOffsetX
                        y: formButtonOffsetY
                        onClicked: {
                            model.setAt(currentIndex, tfNumber2.text, tfName2.text, tfDate2.text, tfAmount2.text, tfStartT2.text, tfStartD2.text, tfFeruT2.text,tfFeruD2.text,tfProtT2.text, tfProtD2.text, tfMaltT2.text,tfMaltD2.text,tfSugT2.text,tfSugD2.text, tfEndT2.text, tfEndD2.text)
                            editRecipeWindow.close()
                        }
                    }

                    Button {
                        id: cancelButton2
                        text: "Abbrechen"
                        font.pointSize: 15
                        width: formButtonWidth
                        height: formButtonHeight
                        x: formButtonOffsetX
                        y: formButtonOffsetY
                        anchors.left: yesButton2.right
                        anchors.leftMargin: formButtonMargin
                        onClicked: editRecipeWindow.close()
                    }

                    RowLayout {
                        id: infoRow2
                        anchors.fill: parent
                        spacing: 0

                        ColumnLayout {
                            id: stdInfo2
                            Layout.alignment: Qt.AlignTop
                            spacing: 10
                            Layout.topMargin: 20
                            Layout.leftMargin: 20

                            Text {id: tName2; text: "Name"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfName2; selectByMouse: true; text: model.at(currentIndex, 257); implicitWidth: infoRow2.width /4; font.pointSize: 14; Layout.leftMargin: tName2.leftPadding}

                            Text {id: tNumber2; text: "Version"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfNumber2; selectByMouse: true; text: model.at(currentIndex, 256); inputMask: "99"; font.pointSize: 14; Layout.leftMargin: tNumber2.leftPadding}

                            Text {id: tDate2; text: "Datum"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfDate2; selectByMouse: true; text: model.at(currentIndex, 258); inputMask: "99-99-9999"; font.pointSize: 14; Layout.leftMargin: tDate2.leftPadding}

                            Text {id: tAmount2; text: "Menge [Liter]"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfAmount2; selectByMouse: true; text: model.at(currentIndex, 259); font.pointSize: 14; Layout.leftMargin: tDate2.leftPadding}

                            Text {id: tDura2; text: "Braudauer [Min]"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            Text {id: ttDura2; text: model.at(currentIndex, 260); color: "white"; font.pointSize: 14; Layout.leftMargin: tAmount2.leftPadding}
                        }

                        GridLayout {
                            Layout.alignment: Qt.AlignTop
                            Layout.topMargin: 10
                            columns: 3
                            columnSpacing: 30
                            rowSpacing: 13

                            Text {id: tRest2; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            Text {id: tTemp2; text: "[°C]"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            Text {id: tbDura2; text: "[Min]"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}

                            Text {id: tStartT2; text: "Einmaischen"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfStartT2; selectByMouse: true; text: model.at(currentIndex, 261); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            TextField {id: tfStartD2; selectByMouse: true; text: model.at(currentIndex, 262); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            //                Text {id: tGlucT2; text: "Glukanase-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            //                TextField {id: tfGlucT2; selectByMouse: true; text: model.at(currentIndex, 263); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            //                TextField {id: tfGlucD2; selectByMouse: true; text: model.at(currentIndex, 264); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            Text {id: tFeruT2; text: "Ferula-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfFeruT2; selectByMouse: true; text: model.at(currentIndex, 263); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            TextField {id: tfFeruD2; selectByMouse: true; text: model.at(currentIndex, 264); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            Text {id: tProtT2; text: "Protease-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfProtT2; selectByMouse: true; text: model.at(currentIndex, 265); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            TextField {id: tfProtD2; selectByMouse: true; text: model.at(currentIndex, 266); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            Text {id: tMaltT2; text: "Maltose-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfMaltT2; selectByMouse: true; text: model.at(currentIndex, 267); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            TextField {id: tfMaltD2; selectByMouse: true; text: model.at(currentIndex, 268); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            Text {id: tSugT2; text: "Zucker-Rast"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfSugT2; selectByMouse: true; text: model.at(currentIndex, 269); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            TextField {id: tfSugD2; selectByMouse: true; text: model.at(currentIndex, 270); font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}

                            Text {id: tEndT2; text: "Abmaischen"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                            TextField {id: tfEndT2; selectByMouse: true; text: model.at(currentIndex, 271); font.pointSize: 14; Layout.leftMargin: tTemp2.leftPadding}
                            Text {id: tfEndD2; text: "0"; color: "white"; font.pointSize: 14; Layout.leftMargin: tbDura2.leftPadding}
                        }
                    }
                }
            }
        }
    }


    //details Button
    Window {
        id: infoRecipeWindow
        width: 800
        height: 480
        flags: "Dialog"
        modality: Qt.WindowModal
        title: "Rezept bearbeiten"
        color: Material.color(Material.Grey, 9)

        Button {
            id: yesButton3
            text: "Rezept laden"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: formButtonOffsetX
            y: formButtonOffsetY
            onClicked: {
                RecipeGraph.recipeToSeries(tfStartT3.text, tfStartD3.text, tfFeruT3.text,tfFeruD3.text,tfProtT3.text, tfProtD3.text, tfMaltT3.text,tfMaltD3.text,tfSugT3.text,tfSugD3.text, tfEndT3.text, tfEndD3.text)
                RecipeGraph.setRecipe(tfNumber3.text, tfName3.text, tfDate3.text, tfAmount3.text, tfStartT3.text, tfStartD3.text, tfFeruT3.text,tfFeruD3.text,tfProtT3.text, tfProtD3.text, tfMaltT3.text,tfMaltD3.text,tfSugT3.text,tfSugD3.text, tfEndT3.text, tfEndD3.text)
                ProgressClass.setRecipe(tfNumber3.text, tfName3.text, tfDate3.text, tfAmount3.text, tfStartT3.text, tfStartD3.text, tfFeruT3.text,tfFeruD3.text,tfProtT3.text, tfProtD3.text, tfMaltT3.text,tfMaltD3.text,tfSugT3.text,tfSugD3.text, tfEndT3.text, tfEndD3.text)
                //                SensorData.setupTimers(RecipeGraph.getTotalX() + 10)
                recipeLoaded()
                infoRecipeWindow.close()
            }
        }

        Button {
            id: cancelButton3
            text: "Abbrechen"
            font.pointSize: 15
            width: formButtonWidth
            height: formButtonHeight
            x: formButtonOffsetX
            y: formButtonOffsetY
            anchors.left: yesButton3.right
            anchors.leftMargin: formButtonMargin
            onClicked: infoRecipeWindow.close()
        }

        RowLayout {
            id: infoRow3
            anchors.fill: parent
            spacing: 0

            ColumnLayout {
                id: stdInfo3
                Layout.alignment: Qt.AlignTop
                spacing: 10
                Layout.topMargin: 20
                Layout.leftMargin: 20

                Text {id: tName3; text: "Name"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfName3; color: "white"; text: model.at(currentIndex, 257); font.pointSize: 14; Layout.leftMargin: tName3.leftPadding}

                Text {id: tNumber3; text: "Version"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfNumber3; color: "white"; text: model.at(currentIndex, 256); font.pointSize: 14; Layout.leftMargin: tNumber3.leftPadding}

                Text {id: tDate3; text: "Datum"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfDate3; color: "white"; text: model.at(currentIndex, 258); font.pointSize: 14; Layout.leftMargin: tDate3.leftPadding}

                Text {id: tAmount3; text: "Menge [Liter]"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfAmount3; color: "white"; text: model.at(currentIndex, 259); font.pointSize: 14; Layout.leftMargin: tDate3.leftPadding}

                Text {id: tDura3; text: "Braudauer [Min]"; leftPadding: 20; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: ttDura3; color: "white"; text: model.at(currentIndex, 260); font.pointSize: 14; Layout.leftMargin: tAmount3.leftPadding}
            }

            GridLayout {
                Layout.alignment: Qt.AlignTop
                Layout.topMargin: 10
                columns: 3
                columnSpacing: 50
                rowSpacing: 20

                Text {id: tRest3; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tTemp3; text: "[°C]"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tbDura3; text: "[Min]"; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}

                Text {id: tStartT3; text: "Einmaischen"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfStartT3; color: "white"; text: model.at(currentIndex, 261); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfStartD3; color: "white"; text: model.at(currentIndex, 262); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                //                Text {id: tGlucT3; text: "Glukanase-Rast"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                //                Text {id: tfGlucT3; color: "white"; text: model.at(currentIndex, 263); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                //                Text {id: tfGlucD3; color: "white"; text: model.at(currentIndex, 264); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                Text {id: tFeruT3; text: "Ferula-Rast"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfFeruT3; color: "white"; text: model.at(currentIndex, 263); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfFeruD3; color: "white"; text: model.at(currentIndex, 264); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                Text {id: tProtT3; text: "Protease-Rast"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfProtT3; color: "white"; text: model.at(currentIndex, 265); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfProtD3; color: "white"; text: model.at(currentIndex, 266); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                Text {id: tMaltT3; text: "Maltose-Rast"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfMaltT3; color: "white"; text: model.at(currentIndex, 267); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfMaltD3; color: "white"; text: model.at(currentIndex, 268); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                Text {id: tSugT3; text: "Zucker-Rast"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfSugT3; color: "white"; text: model.at(currentIndex, 269); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfSugD3; color: "white"; text: model.at(currentIndex, 270); font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}

                Text {id: tEndT3; text: "Abmaischen"; leftPadding: 10; font.pointSize: 16; color: Material.color(Material.Indigo, 3)}
                Text {id: tfEndT3; color: "white"; text: model.at(currentIndex, 271); font.pointSize: 14; Layout.leftMargin: tTemp3.leftPadding}
                Text {id: tfEndD3; text: "0"; color: "white"; font.pointSize: 14; Layout.leftMargin: tbDura3.leftPadding}
            }
        }
    }

    //footer listview
    footer: RowLayout {
        spacing: 0
        z: 2

        Rectangle {
            id: footerNumberRect
            width: recipeView.width
            height: 60
            color: "transparent"
        }
    }

    //header listview
    header: RowLayout {
        spacing: 0
        z: 2

        Rectangle {
            id: titleNumberRect
            width: 1920
            height: recipeView.height / 15
            color: Material.color(Material.Grey, 4)
            border.color: "black"
            Text {
                text: "Name"
                font.pointSize: 16
                font.bold: true
                leftPadding: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            Text  {
                text: "Version"
                font.pointSize: 16
                font.bold: true
                leftPadding: recipeView.width * 4/12
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: "Erstellt am"
                font.pointSize: 16
                font.bold: true
                leftPadding: recipeView.width * 6/12
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: "Aktionen"
                font.pointSize: 16
                font.bold: true
                leftPadding: recipeView.width * 9/12
                anchors.verticalCenter: parent.verticalCenter
            }
            Button {
                width: iconWidth + 5
                height: iconHeight + 5
                icon.source: "pictures/plus.png"
                icon.color: "transparent"
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: "Neues Rezept"
                ToolTip.delay: 500
                ToolTip.timeout: 3000
                icon.width: iconWidth
                icon.height: iconHeight
                x: recipeView.width * 11/12
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    createRecipeWindow.show()
                }
            }
        }
    }

    //list elements
    delegate: Column {
        spacing: 0
        Rectangle {
            id: itemRect
            width: recipeView.width
            height: recipeView.height / itemCount
            color: Material.color(Material.Grey, 1)
            border.color: "black"
            MouseArea {
                anchors.fill: itemRect
                onClicked: recipeView.currentIndex = index
            }
            Text {
                text: model.name
                font.pointSize: 16
                leftPadding: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: model.number
                font.pointSize: 16
                leftPadding: recipeView.width * 4/12
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: model.date
                font.pointSize: 16
                leftPadding: recipeView.width * 6/12
                anchors.verticalCenter: parent.verticalCenter
            }
            Button {
                width: iconWidth + 10
                height: iconHeight + 10
                icon.source: "pictures/folded-newspaper.png"
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: "Informationen"
                ToolTip.delay: 500
                ToolTip.timeout: 3000
                icon.width: iconWidth
                icon.height: iconHeight
                x: recipeView.width * 9/12
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    recipeView.currentIndex = index - 1
                    recipeView.currentIndex = index
                    infoRecipeWindow.show()
                }
            }
            Button {
                width: iconWidth + 10
                height: iconHeight + 10
                icon.source: "pictures/002-edit.png"
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: "Bearbeiten"
                ToolTip.delay: 500
                ToolTip.timeout: 3000
                icon.width: iconWidth
                icon.height: iconHeight
                x: recipeView.width * 10/12
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    recipeView.currentIndex = index
                    editRecipeWindow.show()
                }
            }
            Button {
                width: iconWidth + 10
                height: iconHeight + 10
                icon.source: "pictures/001-close.png"
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: "Löschen"
                ToolTip.delay: 500
                ToolTip.timeout: 3000
                icon.width: iconWidth
                icon.height: iconHeight
                x: recipeView.width * 11/12
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    recipeView.currentIndex = index
                    deleteDialog.show()
                }
            }
        }
    }
}
