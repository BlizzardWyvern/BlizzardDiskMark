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
)

target_compile_definitions(BlizzardIgloo PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_link_libraries(BlizzardIgloo PRIVATE
    Qt6::Quick
    Qt6::Gui
    Qt6::Widgets
    Qt6::Qml
    Qt6::Core
)
target_include_directories(BlizzardIgloo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
