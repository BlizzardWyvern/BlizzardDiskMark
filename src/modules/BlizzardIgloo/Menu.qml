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
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Controls

import BlizzardIgloo

T.Menu {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    margins: 0
    overlap: 0

    delegate: MenuItem { }

    contentItem: ListView {
        implicitHeight: contentHeight
        model: control.contentModel
        interactive: Window.window
                     ? contentHeight + control.topPadding + control.bottomPadding > control.height
                     : false
        clip: true
        currentIndex: control.currentIndex

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 20
        color: control.palette.window
        border.color: control.palette.dark
    }

    T.Overlay.modal: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.5)
    }

    T.Overlay.modeless: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.12)
    }
}
