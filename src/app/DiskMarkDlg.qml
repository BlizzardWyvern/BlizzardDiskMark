import BlizzardIgloo
import BlizzardDiskMark

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: diskMarkApp
    visible: true
    width: 480
    height: 300 + 32
    minimumWidth: 480
    minimumHeight: 300 + 32
    title: {
        var title = ""
        if (diskMarkDlg.m_WindowTitle == null || diskMarkDlg.m_WindowTitle == "") {
            title = qsTr("Blizzard DiskMark")
        }
        else {
            title = diskMarkDlg.m_WindowTitle
        }
        return title + "<0Fill>"
    }

    CDiskMarkDlg {
        id: diskMarkDlg

        function scoreToText(score, latency, unit = m_ComboUnit.currentIndex) {
            switch(unit) {
                case CDiskMarkDlg.SCORE_MBS:
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
    }

    menuBar: MenuBar {
        enabled: !diskMarkDlg.m_DiskBenchStatus
        height: 24
        Menu {
            title: qsTr("&File")
            // Action {
            //     text: qsTr("&Copy") + "\tCtrl + Shift + C"
            //     onTriggered: diskMarkDlg.OnCopy()
            // }
            // Action {
            //     text: qsTr("&Save Text") + "\tCtrl + T"
            //     onTriggered: diskMarkDlg.OnSaveText()
            // }
            // Action {
            //     text: qsTr("&Save Image") + "\tCtrl + S"
            //     onTriggered: diskMarkDlg.OnSaveImage()
            // }
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
                // Action {
                //     text: qsTr("&All 0x00 (0 Fill)")
                //     checkable: true
                //     checked: diskMarkDlg.m_TestData == CDiskMarkDlg.TEST_DATA_ALL0X00
                //     onTriggered: diskMarkDlg.OnModeAll0x00()
                // }
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Default")
                checkable: true
                checked: true
                onTriggered: diskMarkDlg.OnSettingDefault()
            }
            // Action {
            //     text: qsTr("&NVMe SSD")
            //     checkable: true
            //     onTriggered: diskMarkDlg.OnSettingNVMe8()
            // }
            MenuSeparator {}
            // Action {
            //     text: qsTr("&Settings") + "\tCtrl + Q"
            //     onTriggered: diskMarkDlg.OnSettingsQueuesThreads()
            // }
        }
        Menu {
            title: qsTr("&Profile")
            Action {
                text: qsTr("&Default")
                checkable: true
                checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEFAULT
                onTriggered: diskMarkDlg.OnProfileDefault()
            }
            // Action {
            //     text: qsTr("&Peak Performance")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK
            //     onTriggered: diskMarkDlg.OnProfilePeak()
            // }
            // Action {
            //     text: qsTr("&Real World Performance")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL
            //     onTriggered: diskMarkDlg.OnProfileReal()
            // }
            // Action {
            //     text: qsTr("&Demo")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO
            //     onTriggered: diskMarkDlg.OnProfileDemo()
            // }
            // Action {
            //     text: qsTr("&Default [+Mix]")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEFAULT_MIX
            //     onTriggered: diskMarkDlg.OnProfileDefaultMix()
            // }
            // Action {
            //     text: qsTr("&Peak Performance [+Mix]")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX
            //     onTriggered: diskMarkDlg.OnProfilePeakMix()
            // }
            // Action {
            //     text: qsTr("&Real World Performance [+Mix]")
            //     checkable: true
            //     checked: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX
            //     onTriggered: diskMarkDlg.OnProfileRealMix()
            // }
            // MenuSeparator {}
            // Action {
            //     text: qsTr("&Read&Write [+Mix]")
            //     checkable: true
            //     checked: true
            //     onTriggered: diskMarkDlg.OnBenchmarkReadWrite()
            // }
            // Action {
            //     text: qsTr("&Read [+Mix]")
            //     checkable: true
            //     onTriggered: diskMarkDlg.OnBenchmarkReadOnly()
            // }
            // Action {
            //     text: qsTr("&Write [+Mix]")
            //     checkable: true
            //     onTriggered: diskMarkDlg.OnBenchmarkWriteOnly()
            // }
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
            // Action {
            //     text: qsTr("&Font Setting") + "\tCtrl + F"
            //     onTriggered: diskMarkDlg.OnFontSetting()
            // }
            MenuSeparator {}
            Action {
                text: qsTr("&Default")
                checkable: true
                checked: true
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
            // Action {
            //     text: qsTr("&Help") + " [Web]" + "\tF1"
            //     onTriggered: diskMarkDlg.OnHelp()
            // }
            // Action {
            //     text: qsTr("Blizzard World [Web]")
            //     onTriggered: diskMarkDlg.OnBlizzardWorld()
            // }
            MenuSeparator {}
            Action {
                text: qsTr("&About")
                onTriggered: diskMarkDlg.OnAbout()
            }
        }
    }

    GridLayout {
        columns: 3
        rows: 5
        columnSpacing: 4
        rowSpacing: 4
        anchors.margins: 8
        anchors.fill: parent

        Button {
            id: m_ButtonAll
            text: diskMarkDlg.m_buttonTextList[0]
            font.pixelSize: 16
            onClicked: diskMarkDlg.OnAll()
            onHoveredChanged: console.log(m_TestRead0.meter + " " + m_TestWrite0.meter)
            ToolTip.visible: false
        }

        ColumnLayout {
            spacing: 0
            uniformCellSizes: true
            Layout.columnSpan: 2
            Layout.margins: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 192 + 4 + 192
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 192 + 4 + 192
            Layout.verticalStretchFactor: 48
            RowLayout {
                spacing: 4
                Layout.margins: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 192 + 4 + 192
                Layout.minimumHeight: 24
                ComboBox {
                    id: m_ComboCount
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    model: ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
                    currentIndex: diskMarkDlg.m_IndexTestCount
                    onCurrentIndexChanged: diskMarkDlg.m_IndexTestCount = m_ComboCount.currentIndex
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestCount = m_ComboCount.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Test Count")
                    Layout.margins: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 40
                    Layout.minimumHeight: 24
                    Layout.horizontalStretchFactor: 40
                    Layout.verticalStretchFactor: 24
                }

                ComboBox {
                    id: m_ComboSize
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    model: ["16MiB", "32MiB", "64MiB", "128MiB", "256MiB", "512MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB", "64GiB"]
                    currentIndex: 6
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestSize = m_ComboSize.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Test Size")
                    Layout.margins: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 80
                    Layout.minimumHeight: 24
                    Layout.horizontalStretchFactor: 80
                    Layout.verticalStretchFactor: 24
                }

                ComboBox {
                    id: m_ComboDrive
                    property int prev_index: 0
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    model: diskMarkDlg.m_DriveList
                    currentIndex: 0
                    onCurrentIndexChanged: {
                        prev_index = diskMarkDlg.m_IndexTestDrive
                        diskMarkDlg.m_IndexTestDrive = m_ComboDrive.currentIndex
                        if (!diskMarkDlg.m_DiskBenchStatus && m_ComboDrive.currentIndex == m_ComboDrive.count - 1) {
                            m_FileDialog.open()
                        }
                    }
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestDrive = m_ComboDrive.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: {
                        if (diskMarkDlg.m_TestTargetPath === null || diskMarkDlg.m_TestTargetPath === "" || !(m_ComboDrive.currentIndex == m_ComboDrive.count - 1)) {
                            return qsTr("Test Drive")
                        }
                        else {
                            return diskMarkDlg.m_TestTargetPath
                        }
                    }
                    Layout.margins: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 188
                    Layout.minimumHeight: 24
                    Layout.horizontalStretchFactor: 188
                    Layout.verticalStretchFactor: 24
                }

                ComboBox {
                    id: m_ComboUnit
                    enabled: !diskMarkDlg.m_DiskBenchStatus
                    visible: !(diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEFAULT && diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEFAULT_MIX && diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO)
                    model: ["MB/s", "GB/s", "IOPS", "μs"]
                    currentIndex: 0
                    onCurrentValueChanged: diskMarkDlg.m_ValueTestUnit = m_ComboUnit.currentText
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Test Unit")
                    Layout.margins: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 68
                    Layout.minimumHeight: 24
                    Layout.horizontalStretchFactor: 68
                    Layout.verticalStretchFactor: 24
                }
            }
            RowLayout {
                spacing: 4
                uniformCellSizes: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 24
                Label {
                    id: m_ReadUnit
                    text: qsTr("Read") + " (" + m_ComboUnit.currentText + ")"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignBottom
                    background: Rectangle {
                        color: "transparent"
                    }
                    visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                    ToolTip.visible: false
                    Layout.minimumHeight: 24
                }
                Label {
                    id: m_WriteUnit
                    text: qsTr("Write") + " (" + m_ComboUnit.currentText + ")"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignBottom
                    background: Rectangle {
                        color: "transparent"
                    }
                    visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                    ToolTip.visible: false
                    Layout.minimumHeight: 24
                }
            }
        }

        Button {
            id: m_ButtonTest0
            text: diskMarkDlg.m_buttonTextList[1]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[0]
            onClicked: diskMarkDlg.OnTest0()
        }

        Label {
            id: m_TestRead0
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 4 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 6 : 0
            property real read_score: diskMarkDlg.m_readScoreList[index]
            property real read_latency: diskMarkDlg.m_readLatencyList[index]
            text: 
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            ToolTip.text: 
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(read_score, read_latency)
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Label {
            id: m_TestWrite0
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 4 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 6 : 0
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            ToolTip.text: 
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Button {
            id: m_ButtonTest1
            text: diskMarkDlg.m_buttonTextList[2]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[1]
            onClicked: diskMarkDlg.OnTest1()
        }

        Label {
            id: m_TestRead1
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 1
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            ToolTip.text: 
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Label {
            id: m_TestWrite1
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 1
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            ToolTip.text: 
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Button {
            id: m_ButtonTest2
            text: diskMarkDlg.m_buttonTextList[3]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[2]
            onClicked: diskMarkDlg.OnTest2()
        }

        Label {
            id: m_TestRead2
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 2
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            ToolTip.text:
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Label {
            id: m_TestWrite2
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK ? 5 : 
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 2
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            ToolTip.text:
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Button {
            id: m_ButtonTest3
            text: diskMarkDlg.m_buttonTextList[4]
            visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            ToolTip.text: diskMarkDlg.m_buttonToolTipList[3]
            onClicked: diskMarkDlg.OnTest3()
        }

        Label {
            id: m_TestRead3
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK ? 5 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 3
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            ToolTip.text:
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        Label {
            id: m_TestWrite3
            property int index:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK ? 5 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 3
            text:
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            ToolTip.text:
                diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], diskMarkDlg.m_blockSizeList[index])
            meter: diskMarkDlg.calcMeter(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        TextField {
            id: m_Comment
            text: qsTr("Result")
            readOnly: true
            font.pixelSize: 16
            font.weight: Font.Bold
            background: Rectangle {
                color: "transparent"
                border.color: "lightgray"
            }
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 464
            Layout.minimumHeight: 24
            Layout.horizontalStretchFactor: 464
            Layout.verticalStretchFactor: 24
        }
    }

    FolderDialog {
        id: m_FileDialog
        title: qsTr("Select Folder")
        onAccepted: {
            diskMarkDlg.m_TestTargetPath = m_FileDialog.selectedFolder
        }
        onRejected: {
            m_ComboDrive.currentIndex = m_ComboDrive.prev_index
        }
    }
}