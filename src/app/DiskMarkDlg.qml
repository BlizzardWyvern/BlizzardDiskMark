import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import BlizzardDiskMark

ApplicationWindow {
    visible: true
    width: 480
    height: 300
    title: diskMarkDlg.m_WindowTitle

    CDiskMarkDlg {
        id: diskMarkDlg
    }

    menuBar: MenuBar {
        enabled: !diskMarkDlg.m_DiskBenchStatus
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Copy") + "\tCtrl + Shift + C"
                onTriggered: diskMarkDlg.OnCopy()
            }
            Action {
                text: qsTr("&Save Text") + "\tCtrl + T"
                onTriggered: diskMarkDlg.OnSaveText()
            }
            Action {
                text: qsTr("&Save Image") + "\tCtrl + S"
                onTriggered: diskMarkDlg.OnSaveImage()
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Exit") + "\tAlt + F4"
                onTriggered: diskMarkDlg.OnExit()
            }
        }
        Menu {
            title: qsTr("&Settings")
            Menu {
                title: qsTr("&Test Data")
                Action {
                    text: qsTr("&Default (Random)")
                    checkable: true
                    checked: diskMarkDlg.m_TestData == CDiskMarkDlg.TEST_DATA_RANDOM
                    onTriggered: diskMarkDlg.OnModeDefault()
                }
                Action {
                    text: qsTr("&All 0x00 (0 Fill)")
                    checkable: true
                    checked: diskMarkDlg.m_TestData == CDiskMarkDlg.TEST_DATA_ALL0X00
                    onTriggered: diskMarkDlg.OnModeAll0x00()
                }
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Default")
                checkable: true
                checked: true
                onTriggered: diskMarkDlg.OnSettingDefault()
            }
            Action {
                text: qsTr("&NVMe SSD")
                checkable: true
                onTriggered: diskMarkDlg.OnSettingNVMe8()
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Settings") + "\tCtrl + Q"
                onTriggered: diskMarkDlg.OnSettingsQueuesThreads()
            }
        }
        Menu {
            title: qsTr("&Profile")
            Action {
                text: qsTr("&Default")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEFAULT
                onTriggered: diskMarkDlg.OnProfileDefault()
            }
            Action {
                text: qsTr("&Peak Performance")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK
                onTriggered: diskMarkDlg.OnProfilePeak()
            }
            Action {
                text: qsTr("&Real World Performance")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL
                onTriggered: diskMarkDlg.OnProfileReal()
            }
            Action {
                text: qsTr("&Demo")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO
                onTriggered: diskMarkDlg.OnProfileDemo()
            }
            Action {
                text: qsTr("&Default [+Mix]")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEFAULT_MIX
                onTriggered: diskMarkDlg.OnProfileDefaultMix()
            }
            Action {
                text: qsTr("&Peak Performance [+Mix]")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX
                onTriggered: diskMarkDlg.OnProfilePeakMix()
            }
            Action {
                text: qsTr("&Real World Performance [+Mix]")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX
                onTriggered: diskMarkDlg.OnProfileRealMix()
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Read&Write [+Mix]")
                checkable: true
                checked: true
                onTriggered: diskMarkDlg.OnBenchmarkReadWrite()
            }
            Action {
                text: qsTr("&Read [+Mix]")
                checkable: true
                onTriggered: diskMarkDlg.OnBenchmarkReadOnly()
            }
            Action {
                text: qsTr("&Write [+Mix]")
                checkable: true
                onTriggered: diskMarkDlg.OnBenchmarkWriteOnly()
            }
        }
        Menu {
            title: qsTr("&Theme")
            Menu {
                title: qsTr("&Zoom")
                Action {
                    text: qsTr("&100%")
                    checkable: true
                    checked: true
                    onTriggered: console.log("Zoom 100% action triggered")
                }
            }
            Action {
                text: qsTr("&Font Setting") + "\tCtrl + F"
                onTriggered: diskMarkDlg.OnFontSetting()
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Default")
                checkable: true
                onTriggered: console.log("Default theme action triggered")
            }
        }
        Menu {
            title: qsTr("&Language")
            Menu {
                title: "A-N"
                Action {
                    text: "English, [" + qsTr("English") + "]"
                    checkable: true
                    checked: true
                    onTriggered: console.log("English action triggered")
                }
            }
            Menu {
                title: "O-Z"
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&Help") + " [Web]" + "\tF1"
                onTriggered: diskMarkDlg.OnHelp()
            }
            Action {
                text: qsTr("Blizzard World [Web]")
                onTriggered: diskMarkDlg.OnBlizzardWorld()
            }
            MenuSeparator {}
            Action {
                text: qsTr("&About")
                onTriggered: diskMarkDlg.OnAbout()
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        columns: 3
        rows: 5

        Button {
            id: m_ButtonAll
            text: diskMarkDlg.m_buttonTextList[0]
            onClicked: diskMarkDlg.OnAll()
            onHoveredChanged: console.log(diskMarkDlg.m_Profile)
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
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    Layout.fillWidth: true
                    model: ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
                    currentIndex: 4
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestCount = m_ComboCount.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestCount = m_ComboCount.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Test Count")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboSize
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    Layout.fillWidth: true
                    model: ["16MiB", "32MiB", "64MiB", "128MiB", "256MiB", "512MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB", "64GiB"]
                    currentIndex: 6
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestSize = m_ComboSize.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestSize = m_ComboSize.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Test Size")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboDrive
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    Layout.fillWidth: true
                    model: diskMarkDlg.m_DriveList
                    currentIndex: 0
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestDrive = m_ComboDrive.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestDrive = m_ComboDrive.currentText
                    onCurrentTextChanged: diskMarkDlg.OnCbnSelchangeComboDrive()
                    ToolTip.visible: hovered
                    ToolTip.text: diskMarkDlg.m_TestDriveLetter == 99 && !diskMarkDlg.m_TestTargetPath ? diskMarkDlg.m_TestTargetPath : qsTr("Test Drive")
                    Layout.leftMargin: 4
                    Layout.preferredWidth: 188
                    Layout.preferredHeight: 30
                }

                ComboBox {
                    id: m_ComboUnit
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    visible: !(diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEFAULT && diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEFAULT_MIX && diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO)
                    Layout.fillWidth: true
                    model: ["MB/s", "GB/s", "IOPS", "μs"]
                    currentIndex: 0
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestUnit = m_ComboUnit.currentText
                    ToolTip.visible: hovered
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
                    visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                    Layout.preferredWidth: 192
                    Layout.preferredHeight: 24
                }
                Label {
                    id: m_WriteUnit
                    text: qsTr("Write") + " (" + m_ComboUnit.currentText + ")"
                    visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                    Layout.preferredWidth: 192
                    Layout.preferredHeight: 24
                }
            }
        }

        Button {
            id: m_ButtonTest0
            text: diskMarkDlg.m_buttonTextList[1]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[0]
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

        Label {
            id: m_TestRead0
            function scoreToText(score, latency, unit = m_ComboUnit.currentIndex) {
                switch(unit) {
                    case CDiskMarkDlg.SCORE_MBS:
                        console.log("score: " + score)
                        if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO) {
                            return score >= 1000.0 ? score.toFixed(0) : score.toFixed(1)
                        } else {
                            return score >= 1000000.0 ? score.toFixed(0) : score.toFixed(2)
                        }
                        break
                    case CDiskMarkDlg.SCORE_GBS:
                        if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO) {
                            return (score / 1000.0).toFixed(1)
                        } else {
                            return (score / 1000).toFixed(3)
                        }
                        break
                    case CDiskMarkDlg.SCORE_IOPS:
                        if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO) {
                            return ""
                        } else {
                            return ""
                        }
                    case CDiskMarkDlg.SCORE_US:
                        if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO) {
                            if (latency <= 0.0){
                                return "0.0"
                            }
                            else if (latency >= 1000.0) {
                                return latency.toFixed(0)
                            } else {
                                return latency.toFixed(1)
                            }
                        } else {
                            if (latency <= 0.0){
                                return "0.00"
                            }
                            else if (latency >= 1000000.0) {
                                return latency.toFixed(0)
                            } else {
                                return latency.toFixed(2)
                            }
                        }
                    default:
                        return ""
                }
            }
            function scoreToToolTipText(score, latency, blocksize) {
                if (blocksize == -1) {
                    return score.toFixed(3) + " MB/s\n" + (score / 1000).toFixed(3) + " GB/s"
                } else if (score <= 0) {
                    return "0.000 MB/s\n0.000 GB/s\n -- IOPS\n0.000 μs"
                } else {
                    return score.toFixed(3) + " MB/s\n" + (score / 1000).toFixed(3) + " GB/s\n -- IOPS\n" + latency.toFixed(3) + " μs"
                }
            }
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 4 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 6 : 0
            text: 
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            ToolTip.text: 
                scoreToToolTipText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            color: "black"
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            background: Rectangle {
                gradient: Gradient {
                    id: gradient
                    function calcMeter(score, latency) {
                        let meterRatio = 0.0;
                        if (m_ComboUnit.currentText == "μs") {
                            if (latency > 0.0000000001) {
                                meterRatio = 1 - 0.16666666666666 * Math.log10(latency);
                            } else {
                                meterRatio = 0.0
                            }
                        }
                        else {
                            if (score > 0.1) {
                                meterRatio = 0.16666666666666 * Math.log10(score * 10);
                            } else {
                                meterRatio = 0.0
                            }
                        }
                        if (meterRatio > 1.0) {
                            meterRatio = 1.0
                        }
                        return meterRatio
                    }
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? "transparent" : "green" }
                    GradientStop { position: gradient.calcMeter(diskMarkDlg.m_readScoreList[0], diskMarkDlg.m_readLatencyList[0]); color: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? "transparent" : "green" }
                    GradientStop { position: gradient.calcMeter(diskMarkDlg.m_readScoreList[0], diskMarkDlg.m_readLatencyList[0]) + 0.0001; color: "transparent" }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
            ToolTip.visible: mouseArea.containsMouse
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            Layout.leftMargin: 0
            Layout.rightMargin: 4
        }

        Rectangle {
            id: m_TestWrite0
            color: "lightgreen"
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[0] == -1 ? 
                            diskMarkDlg.m_writeScoreList[0].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[0].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_writeScoreList[0] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_writeScoreList[0].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[0].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_writeLatencyList[0].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_writeScoreList[0].toFixed(2)
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
            text: diskMarkDlg.m_buttonTextList[2]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[1]
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[1] == -1 ? 
                            diskMarkDlg.m_readScoreList[1].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[1].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_readScoreList[1] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_readScoreList[1].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[1].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_readLatencyList[1].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_readScoreList[1].toFixed(2)
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[1] == -1 ? 
                            diskMarkDlg.m_writeScoreList[1].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[1].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_writeScoreList[1] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_writeScoreList[1].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[1].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_writeLatencyList[1].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_writeScoreList[1].toFixed(2)
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
            text: diskMarkDlg.m_buttonTextList[3]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[2]
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[2] == -1 ? 
                            diskMarkDlg.m_readScoreList[2].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[2].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_readScoreList[2] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_readScoreList[2].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[2].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_readLatencyList[2].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_readScoreList[2].toFixed(2)
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[2] == -1 ? 
                            diskMarkDlg.m_writeScoreList[2].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[2].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_writeScoreList[2] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_writeScoreList[2].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[2].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_writeLatencyList[2].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_writeScoreList[2].toFixed(2)
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
            text: diskMarkDlg.m_buttonTextList[4]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[3]
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[3] == -1 ? 
                            diskMarkDlg.m_readScoreList[3].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[3].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_readScoreList[3] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_readScoreList[3].toFixed(3) + " MB/s\n" + diskMarkDlg.m_readScoreList[3].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_readLatencyList[3].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_readScoreList[3].toFixed(2)
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
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.visible: hovered
            ToolTip.text: diskMarkDlg.m_blockSizeList[3] == -1 ? 
                            diskMarkDlg.m_writeScoreList[3].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[3].toFixed(3) / 1000 + " GB/s" : 
                          diskMarkDlg.m_writeScoreList[3] <= 0 ?
                            "0.00 MB/s\n0.00 GB/s -- IOPS\n0.00 μs" :
                            diskMarkDlg.m_writeScoreList[3].toFixed(3) + " MB/s\n" + diskMarkDlg.m_writeScoreList[3].toFixed(3) / 1000 + " GB/s\n" + "-- IOPS\n" + diskMarkDlg.m_writeLatencyList[3].toFixed(3) + " μs"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 192
            Layout.preferredHeight: 48
            Text {
                text: diskMarkDlg.m_writeScoreList[3].toFixed(2)
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