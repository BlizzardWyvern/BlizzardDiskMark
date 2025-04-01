add_executable(BlizzardDiskMark 
    DiskMark.ui
    DiskMark.cpp 
    #AboutDlg.cpp 
    DiskBench.cpp 
    DiskMarkDlg.cpp 
    #FontSelectionDlg.cpp 
    #SettingsDlg.cpp
)

target_link_libraries(BlizzardDiskMark PRIVATE Qt6::Widgets)

set_target_properties(BlizzardDiskMark PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)