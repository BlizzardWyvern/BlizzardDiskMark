import ScoreLabel

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Effects

T.Label {
    id: control

    font.pixelSize: 35
    font.family: "Segoe UI"
    font.weight: Font.Bold

    color: "black"
    linkColor: control.palette.link

    rightPadding: 4
    horizontalAlignment: Text.AlignRight
    verticalAlignment: Text.AlignVCenter

    Layout.minimumWidth: 192
    Layout.minimumHeight: 48
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.horizontalStretchFactor: 192
    Layout.verticalStretchFactor: 48

    Layout.margins: 0

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    T.ToolTip.visible: mouseArea.containsMouse

    background: RowLayout {
        spacing: 0
        Layout.margins: 0
        width: parent.width
        height: parent.height
        Rectangle {
            color: "#77db33"
            border.color: "lightgray"
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 0.5; color: "#77db33" }
                GradientStop { position: 1.0; color: "white" }
            }
            Layout.margins: 0
            Layout.fillWidth: parent.width * control.ScoreLabel.meter
            Layout.fillHeight: parent.height
        }
        Rectangle {
            color: "transparent"
            border.color: "lightgray"
            Layout.margins: 0
            Layout.fillWidth: parent.width * (1 - control.ScoreLabel.meter)
            Layout.fillHeight: parent.height
        }
    }
}
