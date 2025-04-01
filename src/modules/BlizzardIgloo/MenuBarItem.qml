/*  
 * Copyright (c) 2025  BlizzardWyvern, Licensed under the LGPL-3.0-only license.
 *   
 * This file incorporates work covered by the following copyright and  
 * license notice:
 *
 *     Copyright (C) 2017 The Qt Company Ltd.
 *
 *     LGPL-3.0-only
 */
 
import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls.impl

import BlizzardIgloo

T.MenuBarItem {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                             implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    spacing: 6
    padding: 0
    leftPadding: 8
    rightPadding: 8

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.palette.buttonText
    }

    background: Rectangle {
        color: control.down || control.highlighted ? control.palette.mid : "transparent"
    }
}
