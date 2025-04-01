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
import QtQuick.Controls

import BlizzardIgloo

T.MenuBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    delegate: MenuBarItem { }

    contentItem: Row {
        spacing: control.spacing
        Repeater {
            model: control.contentModel
        }
    }

    background: Rectangle {
        implicitHeight: 40
        color: "transparent"
    }
}
