// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.Button {
    id: control

    // implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
    //                         implicitContentWidth + leftPadding + rightPadding)
    // implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
    //                          implicitContentHeight + topPadding + bottomPadding)

    // padding: 6
    // horizontalPadding: padding + 2
    // spacing: 6

    font.pixelSize: control.height / 4
    font.family: "Segoe UI"
    font.weight: Font.Bold

    Layout.minimumWidth: 72
    Layout.minimumHeight: 48
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.horizontalStretchFactor: 72
    Layout.verticalStretchFactor: 48

    Layout.margins: 0
    // Layout.topMargin: 4
    // Layout.bottomMargin: 4
    // Layout.leftMargin: 0
    // Layout.rightMargin: 0

    icon.width: 24
    icon.height: 24
    icon.color: control.checked || control.highlighted ? control.palette.brightText :
                control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: control.checked || control.highlighted ? control.palette.brightText :
               control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        border.color: "lightgray"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "#77db33" }
            GradientStop { position: 1.0; color: "white" }
        }
        color: "lightgreen"
    }

    T.ToolTip.visible: hovered
    HoverHandler { 
        enabled: parent.hovered
        cursorShape: Qt.PointingHandCursor
    }
}
