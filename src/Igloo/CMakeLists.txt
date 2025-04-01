qt_add_qml_module(BlizzardIgloo
    URI BlizzardIgloo
    QML_FILES
        Label.qml Button.qml ComboBox.qml Menu.qml MenuBar.qml MenuItem.qml
    SOURCES
    DEPENDENCIES
        QtQuick
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/BlizzardIgloo
)