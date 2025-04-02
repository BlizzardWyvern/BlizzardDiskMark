/*  
 * Copyright (c) 2025  BlizzardWyvern, All rights reserved.
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: aboutDlg
    visible: true
    width: 800
    height: 255
    minimumWidth: 800
    minimumHeight: 255
    title: qsTr("About Blizzard DiskMark")
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowSystemMenuHint | Qt.WindowCloseButtonHint

    RowLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 0

        Image {
            id: logoImage
            source: "qrc:/images/res/DiskMark128.png"
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("https://github.com/BlizzardWyvern")
                }
            }
            Layout.minimumWidth: 128
            Layout.minimumHeight: 128
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 128
            Layout.verticalStretchFactor: 128
        }

        ColumnLayout {
            spacing: 3
            Layout.minimumWidth: 200
            Layout.minimumHeight: 128
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 200
            Layout.verticalStretchFactor: 128
            Text {
                text: qsTr("Blizzard DiskMark ") + VERSION
                font.pixelSize: 22
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://github.com/BlizzardWyvern/BlizzardDiskMark")
                    }
                }
                Layout.minimumWidth: 200
                Layout.minimumHeight: 28
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 28
            }
            Text {
                text: ARCHITECTURE
                font.pixelSize: 18
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                Layout.minimumWidth: 200
                Layout.minimumHeight: 28
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 28
            }
            Text {
                text: BUILDTYPE + qsTr(": 2nd April 2025")
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                Layout.minimumWidth: 200
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 20
            }
                        Text {
                text: qsTr("Made possible by: ") + 
                      "<a href='https://git.kernel.dk/cgit/fio/'>fio - Flexible I/O tester rev. 3.39</a> "
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://git.kernel.dk/cgit/fio/")
                    }
                }
                Layout.minimumWidth: 200
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 20
            }
            Text {
                text: "© 2025 BlizzardWyvern, All rights reserved.\n" + 
                      "© 2017 The Qt Company Ltd.\n" +
                      "© 2007-2021 hiyohiyo" 
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                Layout.minimumWidth: 200
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 20
            }
            Text {
                text: qsTr("Part of this software is licensed under the ") +
                      "<a href='https://www.gnu.org/licenses/lgpl-3.0.html'>GNU LGPL v3.0</a> " +
                      qsTr("license.")
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://www.gnu.org/licenses/lgpl-3.0.html")
                    }
                }
                Layout.minimumWidth: 200
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 20
            }
            Text {
                text: qsTr("Part of this software is licensed under the ") +
                      "<a href='https://opensource.org/licenses/MIT'>MIT</a> " +
                      qsTr("license.")
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://opensource.org/licenses/MIT")
                    }
                }
                Layout.minimumWidth: 200
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 200
                Layout.verticalStretchFactor: 20
            }
        }
    }
}