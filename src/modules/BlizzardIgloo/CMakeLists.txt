qt_add_qml_module(BlizzardIgloo
    STATIC
    URI BlizzardIgloo
    VERSION 1.0
    QML_FILES
        TestLabel.qml 
        Button.qml 
        ComboBox.qml 
        Menu.qml 
        MenuBar.qml 
        MenuBarItem.qml
        MenuItem.qml
        TestRow.qml
        TextField.qml
    OUTPUT_DIRECTORY BlizzardIgloo
)

# # Set a custom directory for the compiled DLL
# set_target_properties(BlizzardIgloo PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/CustomDllDir"
# )
