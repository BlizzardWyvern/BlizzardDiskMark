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

T.MenuItem {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)
                            //  implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 4
    spacing: 0

    icon.width: 12
    icon.height: 12
    icon.color: control.palette.windowText

    contentItem: IconLabel {
        readonly property real arrowPadding: control.subMenu && control.arrow ? control.arrow.width + control.spacing : 0
        readonly property real indicatorPadding: control.checkable && control.indicator ? control.indicator.width + control.spacing : 0
        leftPadding: !control.mirrored ? indicatorPadding : arrowPadding
        rightPadding: control.mirrored ? indicatorPadding : arrowPadding

        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: Qt.AlignLeft

        icon: control.icon
        text: control.text
        font: control.font
        color: control.palette.windowText
    }

    indicator: ColorImage {
        x: control.mirrored ? control.width - width - control.rightPadding : control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        scale: control.checkable ? 0.5 : 0.0
        visible: control.checked
        source: control.checkable ? "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/check.png" : ""
        color: control.palette.windowText
        defaultColor: "#353637"
    }

    arrow: ColorImage {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        visible: control.subMenu
        mirror: control.mirrored
        source: control.subMenu ? "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/arrow-indicator.png" : ""
        color: control.palette.windowText
        defaultColor: "#353637"
    }

    background: Rectangle {
        x: 1
        y: 1
        width: control.width - 2
        height: control.height - 2
        color: control.down ? control.palette.midlight : control.highlighted ? Color.transparent(control.palette.light, 0.5) : "transparent"
    }
}
