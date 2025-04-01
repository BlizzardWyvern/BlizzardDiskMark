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

import BlizzardIgloo

T.TextField {
    id: control

    leftPadding: padding + 4

    color: control.palette.text
    selectionColor: control.palette.highlight
    selectedTextColor: control.palette.highlightedText
    placeholderTextColor: control.palette.placeholderText
    verticalAlignment: TextInput.AlignVCenter

    PlaceholderText {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
        renderType: control.renderType
    }

    background: Rectangle {
        border.width: 1
        color: "transparent"
        border.color: "lightgray"
    }
}
