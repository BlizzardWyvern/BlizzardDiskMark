// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Effects

import BlizzardIgloo

Item {
    id: control

    property alias text: text.text
    property real meter: 0

    T.ToolTip.visible: mouseArea.containsMouse

    Text {
        id:  text
        font.pixelSize: control.height * 35 / 48
        font.family: "Segoe UI"
        font.weight: Font.Bold
        color: "black"
        linkColor: control.palette.link
        rightPadding: 4
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        width: control.width
        height: control.height
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    Rectangle {
        id: scoreRect
        color: "#965ec6" // "#77db33"
        border.color: "lightgray"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "#965ec6" } // "#77db33" }
            GradientStop { position: 1.0; color: "white" }
        }
        x: 0
        y: 0
        z: -1
        width: control.width * control.meter
        height: control.height
    }

    Rectangle {
        id: borderRect
        color: "transparent"
        border.color: "lightgray"
        border.width: 1
        x: 0
        y: 0
        width: control.width
        height: control.height
    }
}
