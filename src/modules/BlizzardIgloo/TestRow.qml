/*  
 * Copyright (c) 2025  BlizzardWyvern, All rights reserved.
 */

import QtQuick.Layouts
import QtQuick.Controls

import BlizzardIgloo

RowLayout {
    id: rowLayout
    spacing: 4
    property int index: 0
    property string buttonText: ""
    property string buttonToolTipText: ""
    property string readText: ""
    property string readToolTipText: ""
    property string writeText: ""
    property string writeToolTipText: ""

    property real read_score: 0
    property real read_latency: 0
    property real write_score: 0
    property real write_latency: 0

    property real read_meter: 0
    property real write_meter: 0

    property bool buttonVisible: true
    property var buttonClicked: function() {
        console.log("Button clicked")
    }
    
    Button {
        id: m_ButtonTest
        text: rowLayout.buttonText
        visible: rowLayout.buttonVisible
        ToolTip.text: rowLayout.buttonToolTipText
        onClicked: rowLayout.buttonClicked.call()
        Layout.minimumWidth: 72
        Layout.minimumHeight: 48
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.horizontalStretchFactor: 72
    }

    RowLayout {
        id: label_row
        spacing: 4
        uniformCellSizes: true
        Layout.minimumWidth: 192 + 4 + 192
        Layout.minimumHeight: 48
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.horizontalStretchFactor: 192 + 4 + 192

        TestLabel {
            id: m_TestRead
            text: rowLayout.readText
            ToolTip.text: rowLayout.readToolTipText
            meter: rowLayout.read_meter
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        TestLabel {
            id: m_TestWrite
            text: rowLayout.writeText
            ToolTip.text: rowLayout.writeToolTipText
            meter: rowLayout.write_meter
            Layout.minimumWidth: 192
            Layout.minimumHeight: 48
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}