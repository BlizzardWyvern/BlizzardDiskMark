import ScoreLabel

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Effects

T.Label {
    id: control

    font.pixelSize: 28
    font.family: "Segoe UI"
    font.weight: Font.Bold

    color: "black"
    linkColor: control.palette.link

    horizontalAlignment: Text.AlignRight
    verticalAlignment: Text.AlignVCenter

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    T.ToolTip.visible: mouseArea.containsMouse

    background: RowLayout {
        spacing: 0
        Rectangle {
            color: "lightgreen"
            // layer.enabled: true
            // layer.effect: MultiEffect {
            //     shadowEnabled: true
            //     shadowHorizontalOffset: 3
            //     shadowVerticalOffset: 3
            //     shadowColor: "black"
            //     shadowBlur: 3
            // }
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 0.5; color: "green" }
                GradientStop { position: 1.0; color: "white" }
            }
            Layout.margins: 0
            Layout.fillWidth: parent.width * control.ScoreLabel.meter
            Layout.fillHeight: parent.height
        }
        Rectangle {
            color: "lightgray"
            Layout.margins: 0
            Layout.fillWidth: parent.width * (1 - control.ScoreLabel.meter)
            Layout.fillHeight: parent.height
        }
        Layout.margins: 0
        width: parent.width
        height: parent.height
    }
}
