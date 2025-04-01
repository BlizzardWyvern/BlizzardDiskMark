// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Effects

T.Label {
    id: control

    property real meter: 0

    font.pixelSize: height * 35 / 48
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
        onClicked: control.meterChanged()
    }

    T.ToolTip.visible: mouseArea.containsMouse

    Rectangle {
        id: scoreRect
        color: "#77db33"
        border.color: "lightgray"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "#77db33" }
            GradientStop { position: 1.0; color: "white" }
        }
        x: 0
        y: 0
        z: -1
        width: control.width * control.meter
        height: control.height
    }

    background: Rectangle {
        id: borderRect
        color: "transparent"
        border.color: "lightgray"
        width: control.width
        height: control.height
    }
}
