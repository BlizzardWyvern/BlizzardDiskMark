// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls
import QtQuick.Templates as T

import BlizzardIgloo

T.ComboBox {
    id: control

    font.pixelSize: control.height * 16 / 24

    delegate: ItemDelegate {
        required property var model
        required property int index

        width: ListView.view.width
        text: model[control.textRole]
        palette.text: control.palette.text
        palette.highlightedText: control.palette.highlightedText
        font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    indicator: ColorImage {
        x: control.mirrored ? control.padding : control.width - width * scale
        y: control.topPadding + (control.availableHeight - height) / 2
        color: control.enabled ? "#965ec6" : control.palette.dark
        defaultColor: "#353637"
        source: "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/double-arrow.png"
        opacity: enabled ? 1 : 0.3
        scale: (control.height / height) * 0.75
    }

    contentItem: T.TextField {
        leftPadding: 4

        text: control.editable ? control.editText : control.displayText

        enabled: control.editable
        autoScroll: control.editable
        readOnly: control.down
        inputMethodHints: control.inputMethodHints
        validator: control.validator
        selectByMouse: control.selectTextByMouse

        color: control.editable ? control.palette.text : control.palette.buttonText
        selectionColor: control.palette.highlight
        selectedTextColor: control.palette.highlightedText
        verticalAlignment: Text.AlignVCenter

        background: Rectangle {
            visible: control.enabled && control.editable && !control.flat
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: "lightgray"
            color: control.palette.base
        }
    }

    background: Rectangle {
        implicitWidth: 140
        implicitHeight: 40

        color: "white"
        border.color: "lightgray"
    }

    popup: T.Popup {
        y: control.height
        width: control.width
        height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
        topMargin: 6
        bottomMargin: 6
        palette: control.palette

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.delegateModel
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0

            Rectangle {
                z: 10
                width: parent.width
                height: parent.height
                color: "transparent"
                border.color: "lightgray"
            }

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: control.palette.window
        }
    }
}
