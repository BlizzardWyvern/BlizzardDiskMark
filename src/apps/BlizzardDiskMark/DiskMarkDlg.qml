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
        function buttonText(type, size, queues, threads, unit) {
            var text = ""
            if (size >= 1024) {
                if (type == CDiskMarkDlg.BENCH_RND) {
                    if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX) {
                        switch (unit) {
                            case CDiskMarkDlg.SCORE_IOPS:
                                text = "RND" + size / 1024 + "M\n(IOPS)"
                                break
                            case CDiskMarkDlg.SCORE_GBS:
                                text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                                break
                            case CDiskMarkDlg.SCORE_US:
                                text = "RND" + size / 1024 + "M\n(μs)"
                                break
                            default:
                                text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                                break
                        }
                    }
                    else {
                        switch (unit) {
                            case CDiskMarkDlg.SCORE_GBS:
                                text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                                break
                            default:
                                text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                                break
                        }
                    }
                }
                else {
                    switch (unit) {
                        case CDiskMarkDlg.SCORE_GBS:
                            text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                            break
                        default:
                            text = "RND" + size / 1024 + "M\nQ" + queues + "T" + threads
                            break
                    }
                }
            }
            else {
                if (type == CDiskMarkDlg.BENCH_RND) {
                    if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX) {
                        switch (unit) {
                            case CDiskMarkDlg.SCORE_IOPS:
                                text = "RND" + size + "K\n(IOPS)"
                                break
                            case CDiskMarkDlg.SCORE_GBS:
                                text = "RND" + size + "K\nQ" + queues + "T" + threads
                                break
                            case CDiskMarkDlg.SCORE_US:
                                text = "RND" + size + "K\n(μs)"
                                break
                            default:
                                text = "RND" + size + "K\nQ" + queues + "T" + threads
                                break
                        }
                    }
                    else {
                        switch (unit) {
                            case CDiskMarkDlg.SCORE_GBS:
                                text = "RND" + size + "K\nQ" + queues + "T" + threads
                                break
                            default:
                                text = "RND" + size + "K\nQ" + queues + "T" + threads
                                break
                        }
                    }
                }
                else {
                    switch (unit) {
                        case CDiskMarkDlg.SCORE_GBS:
                            text = "RND" + size + "K\nQ" + queues + "T" + threads
                            break
                        default:
                            text = "RND" + size + "K\nQ" + queues + "T" + threads
                            break
                    }
                }
            }
            return text
        }
        function buttonDemoText(benchType, blockSize, benchQueues, benchThreads, unitIndex) {
            switch (benchType) {
                case CDiskMarkDlg.BENCH_RND:
                    if (blockSize > 1000) {
                        "RND " + blockSize / 1024 + "MiB, Q=" + benchQueues + ", T=" + benchThreads
                    } else {
                        "RND " + blockSize + "MiB, Q=" + benchQueues + ", T=" + benchThreads
                    }
                case CDiskMarkDlg.BENCH_SEQ:
                    if (blockSize > 1000) {
                        "SEQ " + blockSize / 1024 + "MiB, Q=" + benchQueues + ", T=" + benchThreads
                    } else {
                        "SEQ " + blockSize + "MiB, Q=" + benchQueues + ", T=" + benchThreads
                    }
            }
        }
        function setButtonText(benchType, blockSize, benchQueues, benchThreads, unitIndex) {
            if (diskMarkDlg.m_DiskBenchStatus) {
                return qsTr("Stop")
            }
            switch (diskMarkDlg.m_Profile) {
                case CDiskMarkDlg.PROFILE_DEMO:
                    return diskMarkDlg.buttonDemoText(benchType, blockSize, benchQueues, benchThreads, unitIndex)
                case CDiskMarkDlg.PROFILE_REAL:
                    return diskMarkDlg.buttonText(CDiskMarkDlg.BENCH_SEQ, 1024, 1, 1, CDiskMarkDlg.SCORE_MBS)
                case CDiskMarkDlg.PROFILE_REAL_MIX:
                    return diskMarkDlg.buttonText(CDiskMarkDlg.BENCH_SEQ, 1024, 1, 1, CDiskMarkDlg.SCORE_MBS)
                default:
                    return diskMarkDlg.buttonText(benchType, blockSize, benchQueues, benchThreads, unitIndex)
            }   
        }
        function getButtonToolTipText(type, size, queues, threads, unit) {
            let text = "";

            if (size >= 1024) {
                if (type === CDiskMarkDlg.BENCH_RND) {
                    if (unit === CDiskMarkDlg.SCORE_IOPS) {
                        text = `Random ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(IOPS)`;
                    } else if (unit === CDiskMarkDlg.SCORE_US) {
                        text = `Random ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(μs)`;
                    } else if (unit === CDiskMarkDlg.SCORE_GBS) {
                        text = `Random ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(GB/s)`;
                    } else {
                        text = `Random ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(MB/s)`;
                    }
                } else {
                    if (unit === CDiskMarkDlg.SCORE_GBS) {
                        text = `Sequential ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(GB/s)`;
                    } else {
                        text = `Sequential ${size / 1024}MiB\nQueues=${queues}\nThreads=${threads}\n(MB/s)`;
                    }
                }
            } else {
                if (type === CDiskMarkDlg.BENCH_RND) {
                    if (unit === CDiskMarkDlg.SCORE_IOPS) {
                        text = `Random ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(IOPS)`;
                    } else if (unit === CDiskMarkDlg.SCORE_US) {
                        text = `Random ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(μs)`;
                    } else if (unit === CDiskMarkDlg.SCORE_GBS) {
                        text = `Random ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(GB/s)`;
                    } else {
                        text = `Random ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(MB/s)`;
                    }
                } else {
                    if (unit === CDiskMarkDlg.SCORE_GBS) {
                        text = `Sequential ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(GB/s)`;
                    } else {
                        text = `Sequential ${size}KiB\nQueues=${queues}\nThreads=${threads}\n(MB/s)`;
                    }
                }
            }
            return text;
        }
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

        function scoreToToolTipText(score, latency) {
            if (diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO) {
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
            // MenuSeparator {}
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
            // MenuSeparator {}
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
            // MenuSeparator {}
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

        RowLayout {
            spacing: 4
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 72 + 4 + 192 + 4 + 192
            Layout.verticalStretchFactor: 48

            Button {
                id: m_ButtonAll
                text: diskMarkDlg.m_DiskBenchStatus ? qsTr("Stop") : qsTr("All")
                font.pixelSize: height / 3
                onClicked: diskMarkDlg.OnAll()
                ToolTip.visible: false
            }

            ColumnLayout {
                spacing: 0
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
                    Layout.horizontalStretchFactor: 192 + 4 + 192
                    Layout.verticalStretchFactor: 24
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
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumWidth: 192 + 4 + 192
                    Layout.minimumHeight: 24
                    Layout.horizontalStretchFactor: 192 + 4 + 192
                    Layout.verticalStretchFactor: 24
                    Label {
                        id: m_ReadUnit
                        text: qsTr("Read") + " (" + m_ComboUnit.currentText + ")"
                        font.pixelSize: height * 16 / 24
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        background: Rectangle {
                            color: "transparent"
                        }
                        visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                        ToolTip.visible: false
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumWidth: 192
                        Layout.minimumHeight: 24
                        Layout.horizontalStretchFactor: 192
                        Layout.verticalStretchFactor: 24
                    }
                    Label {
                        id: m_WriteUnit
                        text: qsTr("Write") + " (" + m_ComboUnit.currentText + ")"
                        font.pixelSize: height * 16 / 24
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        background: Rectangle {
                            color: "transparent"
                        }
                        visible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
                        ToolTip.visible: false
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumWidth: 192
                        Layout.minimumHeight: 24
                        Layout.horizontalStretchFactor: 192
                        Layout.verticalStretchFactor: 24
                    }
                }
            }
        }


        TestRow {
            id: m_Test0
            index: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 4 :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 6 : 0
            buttonText: diskMarkDlg.setButtonText(diskMarkDlg.m_benchTypeList[m_Test0.index], diskMarkDlg.m_blockSizeList[m_Test0.index], diskMarkDlg.m_benchQueuesList[m_Test0.index], diskMarkDlg.m_benchThreadsList[m_Test0.index], m_ComboUnit.currentIndex)
            buttonToolTipText: diskMarkDlg.getButtonToolTipText(diskMarkDlg.m_benchTypeList[m_Test0.index], diskMarkDlg.m_blockSizeList[m_Test0.index], diskMarkDlg.m_benchQueuesList[m_Test0.index], diskMarkDlg.m_benchThreadsList[m_Test0.index], m_ComboUnit.currentIndex)
            buttonClicked: function() {diskMarkDlg.OnTest0()}
            readText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                    diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            readToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[m_Test0.index], diskMarkDlg.m_readLatencyList[m_Test0.index])
            writeText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                    diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            writeToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[m_Test0.index], diskMarkDlg.m_writeLatencyList[m_Test0.index])
            read_score: diskMarkDlg.m_readScoreList[m_Test0.index]
            read_latency: diskMarkDlg.m_readLatencyList[m_Test0.index]
            write_score: diskMarkDlg.m_writeScoreList[m_Test0.index]
            write_latency: diskMarkDlg.m_writeLatencyList[m_Test0.index]
            read_meter: diskMarkDlg.calcMeter(m_Test0.read_score, m_Test0.read_latency)
            write_meter: diskMarkDlg.calcMeter(m_Test0.write_score, m_Test0.write_latency)
            buttonVisible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        TestRow {
            id: m_Test1
            index: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 1
            buttonText: diskMarkDlg.setButtonText(diskMarkDlg.m_benchTypeList[m_Test1.index], diskMarkDlg.m_blockSizeList[m_Test1.index], diskMarkDlg.m_benchQueuesList[m_Test1.index], diskMarkDlg.m_benchThreadsList[m_Test1.index], m_ComboUnit.currentIndex)
            buttonToolTipText: diskMarkDlg.getButtonToolTipText(diskMarkDlg.m_benchTypeList[m_Test1.index], diskMarkDlg.m_blockSizeList[m_Test1.index], diskMarkDlg.m_benchQueuesList[m_Test1.index], diskMarkDlg.m_benchThreadsList[m_Test1.index], m_ComboUnit.currentIndex)
            buttonClicked: function() {diskMarkDlg.OnTest1()}
            readText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            readToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[m_Test1.index], diskMarkDlg.m_readLatencyList[m_Test1.index])
            writeText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            writeToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[m_Test1.index], diskMarkDlg.m_writeLatencyList[m_Test1.index])
            read_score: diskMarkDlg.m_readScoreList[m_Test1.index]
            read_latency: diskMarkDlg.m_readLatencyList[m_Test1.index]
            write_score: diskMarkDlg.m_writeScoreList[m_Test1.index]
            write_latency: diskMarkDlg.m_writeLatencyList[m_Test1.index]
            read_meter: diskMarkDlg.calcMeter(m_Test1.read_score, m_Test1.read_latency)
            write_meter: diskMarkDlg.calcMeter(m_Test1.write_score, m_Test1.write_latency)
            buttonVisible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        TestRow {
            id: m_Test2
            index: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 2
            buttonText: diskMarkDlg.setButtonText(diskMarkDlg.m_benchTypeList[m_Test2.index], diskMarkDlg.m_blockSizeList[m_Test2.index], diskMarkDlg.m_benchQueuesList[m_Test2.index], diskMarkDlg.m_benchThreadsList[m_Test2.index], m_ComboUnit.currentIndex)
            buttonToolTipText: diskMarkDlg.getButtonToolTipText(diskMarkDlg.m_benchTypeList[m_Test2.index], diskMarkDlg.m_blockSizeList[m_Test2.index], diskMarkDlg.m_benchQueuesList[m_Test2.index], diskMarkDlg.m_benchThreadsList[m_Test2.index], m_ComboUnit.currentIndex)
            buttonClicked: function() {diskMarkDlg.OnTest2()}
            readText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            readToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[m_Test2.index], diskMarkDlg.m_readLatencyList[m_Test2.index])
            writeText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            writeToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[m_Test2.index], diskMarkDlg.m_writeLatencyList[m_Test2.index])
            read_score: diskMarkDlg.m_readScoreList[m_Test2.index]
            read_latency: diskMarkDlg.m_readLatencyList[m_Test2.index]
            write_score: diskMarkDlg.m_writeScoreList[m_Test2.index]
            write_latency: diskMarkDlg.m_writeLatencyList[m_Test2.index]
            read_meter: diskMarkDlg.calcMeter(m_Test2.read_score, m_Test2.read_latency)
            write_meter: diskMarkDlg.calcMeter(m_Test2.write_score, m_Test2.write_latency)
            buttonVisible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        TestRow {
            id: m_Test3
            index: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_DEMO ? 8 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ? 5 :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ? 7 : 3
            buttonText: diskMarkDlg.setButtonText(diskMarkDlg.m_benchTypeList[m_Test3.index], diskMarkDlg.m_blockSizeList[m_Test3.index], diskMarkDlg.m_benchQueuesList[m_Test3.index], diskMarkDlg.m_benchThreadsList[m_Test3.index], m_ComboUnit.currentIndex)
            buttonToolTipText: diskMarkDlg.getButtonToolTipText(diskMarkDlg.m_benchTypeList[m_Test3.index], diskMarkDlg.m_blockSizeList[m_Test3.index], diskMarkDlg.m_benchQueuesList[m_Test3.index], diskMarkDlg.m_benchThreadsList[m_Test3.index], m_ComboUnit.currentIndex)
            buttonClicked: function() {diskMarkDlg.OnTest3()}
            readText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_readScoreList[index], diskMarkDlg.m_readLatencyList[index])
            readToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_readScoreList[m_Test3.index], diskMarkDlg.m_readLatencyList[m_Test3.index])
            writeText: diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_PEAK_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
            diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL || diskMarkDlg.m_Profile == CDiskMarkDlg.PROFILE_REAL_MIX ?
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index], CDiskMarkDlg.SCORE_MBS) :
                diskMarkDlg.scoreToText(diskMarkDlg.m_writeScoreList[index], diskMarkDlg.m_writeLatencyList[index])
            writeToolTipText: diskMarkDlg.scoreToToolTipText(diskMarkDlg.m_writeScoreList[m_Test3.index], diskMarkDlg.m_writeLatencyList[m_Test3.index])
            read_score: diskMarkDlg.m_readScoreList[m_Test3.index]
            read_latency: diskMarkDlg.m_readLatencyList[m_Test3.index]
            write_score: diskMarkDlg.m_writeScoreList[m_Test3.index]
            write_latency: diskMarkDlg.m_writeLatencyList[m_Test3.index]
            read_meter: diskMarkDlg.calcMeter(m_Test3.read_score, m_Test3.read_latency)
            write_meter: diskMarkDlg.calcMeter(m_Test3.write_score, m_Test3.write_latency)
            buttonVisible: diskMarkDlg.m_Profile != CDiskMarkDlg.PROFILE_DEMO
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 48
            Layout.horizontalStretchFactor: 192
            Layout.verticalStretchFactor: 48
        }

        TextField {
            id: m_Comment
            text: qsTr("Result")
            readOnly: true
            font.pixelSize: height * 16 / 24
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