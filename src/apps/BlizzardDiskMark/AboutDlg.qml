import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: aboutDlg
    visible: true
    width: 480
    height: 152
    minimumWidth: 480
    minimumHeight: 152
    title: qsTr("About Blizzard DiskMark")
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowSystemMenuHint | Qt.WindowCloseButtonHint

    RowLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 0

        Image {
            id: logoImage
            source: "/images/res/DiskMark.ico"
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
            Layout.minimumWidth: 340
            Layout.minimumHeight: 128
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.horizontalStretchFactor: 340
            Layout.verticalStretchFactor: 128
            Text {
                text: qsTr("Blizzard DiskMark 1.0.0")
                font.pixelSize: 22
                font.bold: true
                color: "black"
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://github.com/BlizzardWyvern/BlizzardDiskMark")
                    }
                }
                Layout.minimumWidth: 340
                Layout.minimumHeight: 28
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 340
                Layout.verticalStretchFactor: 28
            }
            Text {
                text: qsTr("x64")
                font.pixelSize: 18
                font.bold: true
                color: "black"
                Layout.minimumWidth: 340
                Layout.minimumHeight: 28
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 340
                Layout.verticalStretchFactor: 28
            }
            Text {
                text: qsTr("Release: 29th May 2025")
                font.pixelSize: 16
                color: "black"
                Layout.minimumWidth: 340
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 340
                Layout.verticalStretchFactor: 20
            }
            Text {
                text: qsTr("© 2025 BlizzardWyvern")
                font.pixelSize: 16
                color: "black"
                Layout.minimumWidth: 340
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 340
                Layout.verticalStretchFactor: 20
            }
            Text {
                text: qsTr("License")
                font.pixelSize: 16
                color: "black"
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        Qt.openUrlExternally("https://github.com/BlizzardWyvern/BlizzardDiskMark/blob/main/LICENSE")
                    }
                }
                Layout.minimumWidth: 340
                Layout.minimumHeight: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.horizontalStretchFactor: 340
                Layout.verticalStretchFactor: 20
            }
        }
    }
}