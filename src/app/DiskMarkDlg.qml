import QtQuick
import QtQuick.Controls
import BlizzardDiskMark

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("BlizzardDiskMark")

    CDiskMarkDlg {
        id: diskMarkDlg
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered")
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Exit")
                onTriggered: Qt.quit
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                //onTriggered: diskMarkDlg.showAboutDlg()
            }
        }
    }

    Label {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}