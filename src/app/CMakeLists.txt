add_executable(BlizzardDiskMark
    application.qrc
    DiskMark.cpp 
    AboutDlg.cpp 
    DiskBench.cpp 
    DiskMarkDlg.cpp 
    #FontSelectionDlg.cpp 
    SettingsDlg.cpp
)

qt_add_qml_module(BlizzardDiskMark
    URI BlizzardDiskMark
    QML_FILES 
        DiskMarkDlg.qml
    SOURCES 
        DiskMarkDlg.cpp DiskMarkDlg.h
    NO_RESOURCE_TARGET_PATH
)

target_link_libraries(BlizzardDiskMark PRIVATE Qt6::Widgets Qt6::Gui Qt6::Quick)

set(QT_QML_GENERATE_QMLLS_INI ON)

set_target_properties(BlizzardDiskMark PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)