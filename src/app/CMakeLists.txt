qt_policy(SET QTP0004 NEW)

add_executable(BlizzardDiskMark
    application.qrc
    DiskMark.cpp 
    AboutDlg.cpp 
    DiskBench.cpp 
    DiskMarkDlg.cpp 
    #FontSelectionDlg.cpp 
    SettingsDlg.cpp
)

qt_add_qml_module(ScoreLabel
    URI ScoreLabel
    QML_FILES
        ScoreLabel/Label.qml ScoreLabel/Button.qml ScoreLabel/ComboBox.qml
    SOURCES 
        ScoreLabel.cpp ScoreLabel.h
    DEPENDENCIES
        QtQuick
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ScoreLabel
)

qt_add_qml_module(BlizzardDiskMark
    URI BlizzardDiskMark
    QML_FILES 
        DiskMarkDlg.qml
    SOURCES 
        DiskMarkDlg.cpp DiskMarkDlg.h
    DEPENDENCIES
        QtQuick
    NO_RESOURCE_TARGET_PATH
)

target_link_libraries(BlizzardDiskMark PRIVATE Qt6::Widgets Qt6::Gui Qt6::Quick ScoreLabel)

set(QT_QML_GENERATE_QMLLS_INI ON)

set_target_properties(BlizzardDiskMark PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)