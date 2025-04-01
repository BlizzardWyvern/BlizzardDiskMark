import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BlizzardDiskMark

ApplicationWindow {
    visible: true
    width: 480
    height: 300
    title: qsTr("BlizzardDiskMark")

    CDiskMarkDlg {
        id: diskMarkDlg
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Save Text") + "\tCtrl + T"
                onTriggered: console.log("Save action triggered")
            }
            Action {
                text: qsTr("Save &Image") + "\tCtrl + S"
                onTriggered: console.log("Save image action triggered")
            }
            Action {
                text: qsTr("&Copy") + "\tCtrl + Shift + C"
                onTriggered: console.log("Copy action triggered")
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Exit") + "\tAlt + F4"
                onTriggered: console.log("Exit action triggered")
            }
        }
        Menu {
            title: qsTr("&Settings")
            Action {
                text: qsTr("&Test Data")
                onTriggered: console.log("Test data action triggered")
            }
            Action {
                text: qsTr("&Default Random")
                onTriggered: console.log("Default random action triggered")
            }
            Action {
                text: qsTr("&All Zero")
                onTriggered: console.log("All zero action triggered")
            }
            Action {
                text: qsTr("&Settings") + "\tCtrl + Q"
                onTriggered: console.log("Settings action triggered")
            }
        }
        Menu {
            title: qsTr("&Profile")
            Action {
                text: qsTr("&Profile Default")
                onTriggered: console.log("Profile default action triggered")
            }
            Action {
                text: qsTr("&Profile Peak")
                onTriggered: console.log("Profile peak action triggered")
            }
            Action {
                text: qsTr("&Profile Real")
                onTriggered: console.log("Profile real action triggered")
            }
            Action {
                text: qsTr("&Profile Demo")
                onTriggered: console.log("Profile demo action triggered")
            }
        }
        Menu {
            title: qsTr("&Theme")
            Action {
                text: qsTr("&Zoom")
                onTriggered: console.log("Zoom action triggered")
            }
            Action {
                text: qsTr("&Auto")
                onTriggered: console.log("Auto action triggered")
            }
            Action {
                text: qsTr("&Font Setting")
                onTriggered: console.log("Font setting action triggered")
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&Help") + " [Web]" + "\tF1"
                onTriggered: console.log("Help action triggered")
            }
            Action {
                text: qsTr("&About")
                onTriggered: console.log("About action triggered")
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        columns: 3
        rows: 5

        Button {
            id: m_ButtonAll
            text: qsTr("All")
            onClicked: diskMarkDlg.OnAll()
            Layout.preferredWidth: 72
            Layout.preferredHeight: 48
            HoverHandler {
                enabled: parent.hovered
                cursorShape: Qt.PointingHandCursor
            }
        }

        ColumnLayout {
            Layout.columnSpan: 2
            RowLayout {
                Layout.fillWidth: true
                ComboBox {
                    id: m_ComboCount
                    Layout.fillWidth: true
                    model: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
                    currentIndex: 4
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestCount = m_ComboCount.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestCount = m_ComboCount.currentText
                    ToolTip.text: qsTr("Test Count")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboSize
                    Layout.fillWidth: true
                    model: ["16MiB", "32MiB", "64MiB", "128MiB", "256MiB", "512MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB", "64GiB"]
                    currentIndex: 6
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestSize = m_ComboSize.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestSize = m_ComboSize.currentText
                    ToolTip.text: qsTr("Test Size")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboDrive
                    Layout.fillWidth: true
                    model: diskMarkDlg.m_DriveList
                    currentIndex: 0
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestDrive = m_ComboDrive.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestDrive = m_ComboDrive.currentText
                    onCurrentTextChanged: diskMarkDlg.OnCbnSelchangeComboDrive()
                    ToolTip.text: qsTr("Test Drive")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 188
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboUnit
                    Layout.fillWidth: true
                    model: ["MB/s", "GB/s", "IOPS", "μs"]
                    currentIndex: 0
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestUnit = m_ComboUnit.currentText
                    ToolTip.text: qsTr("Test Unit")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 68
                    Layout.preferredHeight: 30
                }
            }
            RowLayout {
                Label {
                    id: m_ReadUnit
                    text: qsTr("Read") + " (" + m_ComboUnit.currentText + ")"
                    Layout.preferredWidth: 192
                    Layout.preferredHeight: 24
                }
                Label {
                    id: m_WriteUnit
                    text: qsTr("Write") + " (" + m_ComboUnit.currentText + ")"
                    Layout.preferredWidth: 192
                    Layout.preferredHeight: 24
                }
            }
        }

        Button {
            id: m_ButtonTest0
            text: qsTr("1")
            onClicked: diskMarkDlg.OnTest0()
            Layout.preferredWidth: 72
            Layout.preferredHeight: 48
            HoverHandler {
                enabled: parent.hovered
                cursorShape: Qt.PointingHandCursor
            }
            Layout.topMargin: 4
            Layout.bottomMargin: 4
            Layout.leftMargin: 0
            Layout.rightMargin: 0
        }

        Rectangle {
            id: m_TestRead0
            objectName: "m_TestRead0"
            color: "lightblue"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_ReadScore0.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Rectangle {
            id: m_TestWrite0
            color: "lightgreen"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_WriteScore0.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Button {
            id: m_ButtonTest1
            text: qsTr("2")
            onClicked: diskMarkDlg.OnTest1()
            Layout.preferredWidth: 72
            Layout.preferredHeight: 48
            HoverHandler {
                enabled: parent.hovered
                cursorShape: Qt.PointingHandCursor
            }
            Layout.topMargin: 4
            Layout.bottomMargin: 4
            Layout.leftMargin: 0
            Layout.rightMargin: 0
        }

        Rectangle {
            id: m_TestRead1
            color: "lightblue"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_ReadScore1.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Rectangle {
            id: m_TestWrite1
            color: "lightgreen"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_WriteScore1.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Button {
            id: m_ButtonTest2
            text: qsTr("3")
            onClicked: diskMarkDlg.OnTest2()
            Layout.preferredWidth: 72
            Layout.preferredHeight: 48
            HoverHandler {
                enabled: parent.hovered
                cursorShape: Qt.PointingHandCursor
            }
            Layout.topMargin: 4
            Layout.bottomMargin: 4
            Layout.leftMargin: 0
            Layout.rightMargin: 0
        }

        Rectangle {
            id: m_TestRead2
            color: "lightblue"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_ReadScore2.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Rectangle {
            id: m_TestWrite2
            color: "lightgreen"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_WriteScore2.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Button {
            id: m_ButtonTest3
            text: qsTr("4")
            onClicked: diskMarkDlg.OnTest3()
            Layout.preferredWidth: 72
            Layout.preferredHeight: 48
            HoverHandler {
                enabled: parent.hovered
                cursorShape: Qt.PointingHandCursor
            }
            Layout.topMargin: 4
            Layout.bottomMargin: 4
            Layout.leftMargin: 0
            Layout.rightMargin: 0
        }

        Rectangle {
            id: m_TestRead3
            color: "lightblue"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_ReadScore3.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Rectangle {
            id: m_TestWrite3
            color: "lightgreen"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_WriteScore3.toFixed(2)
                color: "black"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        TextField {
            id: m_Comment
            text: qsTr("Result")
            readOnly: true
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.preferredWidth: 464
            Layout.preferredHeight: 24
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 4
            Layout.rightMargin: 4
        }
    }
}