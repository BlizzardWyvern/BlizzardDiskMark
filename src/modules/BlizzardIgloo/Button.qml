// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.Button {
    id: control

    implicitWidth: 72
    implicitHeight: 48

    font.pixelSize: control.height / 4
    font.family: "Segoe UI"
    font.weight: Font.Bold

    T.ToolTip.visible: hovered

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.checked || control.highlighted ? control.palette.brightText :
               control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: control.width
        height: control.height
    }

    background: Rectangle {
        border.color: "lightgray"
        border.width: 1
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "#965ec6" } // "#77db33" }
            GradientStop { position: 1.0; color: "white" }
        }
        color: "#965ec6"
    }

    HoverHandler { 
        enabled: parent.hovered
        cursorShape: Qt.PointingHandCursor
    }
}
