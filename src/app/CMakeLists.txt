add_executable(BlizzardDiskMark
    application.qrc
    DiskMark.cpp 
    DiskBench.cpp 
    DiskMarkDlg.cpp 
    # FontSelectionDlg.cpp 
    # SettingsDlg.cpp
    # AboutDlg.cpp 
)

qt_add_qml_module(BlizzardDiskMark
    URI BlizzardDiskMark
    QML_FILES 
        DiskMarkDlg.qml
    SOURCES 
        DiskMarkDlg.cpp DiskMarkDlg.h
    DEPENDENCIES
        QtQuick
        QtQuick.Controls
        QtQuick.Layouts
        QtQuick.Dialogs
    NO_RESOURCE_TARGET_PATH
)

target_link_libraries(BlizzardDiskMark PRIVATE
    Qt6::Widgets
    Qt6::Quick
    BlizzardIglooplugin
    )

set_target_properties(BlizzardDiskMark PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Add a post-build step to run windeployqt for Release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET BlizzardDiskMark POST_BUILD
        COMMAND ${Qt6_DIR}/../../../bin/windeployqt.exe 
            --release --no-translations
            --qmldir ${CMAKE_SOURCE_DIR}/src/app 
            $<TARGET_FILE:BlizzardDiskMark>
        COMMENT "Running windeployqt on BlizzardDiskMark executable with QML directory"
    )
endif()

# Add WiX build step if on Windows
if(WIN32)
    find_program(WIX_EXECUTABLE wix.exe REQUIRED)

    set(WIX_SOURCE ${CMAKE_SOURCE_DIR}/installer/BlizzardDiskMark.wxs)
    set(WIX_PREPROCESSED ${CMAKE_BINARY_DIR}/installer/BlizzardDiskMark_preprocessed.wxs)
    set(WIX_OUTPUT ${CMAKE_BINARY_DIR}/installer/BlizzardDiskMark.msi)
    set(REPLACE_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/replace_in_file.py)
    
    # Preprocess the .wxs file
    add_custom_command(
        OUTPUT ${WIX_PREPROCESSED}
        COMMAND ${PYTHON_EXECUTABLE} ${REPLACE_SCRIPT}
            ${WIX_SOURCE} ${WIX_PREPROCESSED}
            "@CMAKE_BINARY_DIR@" "${CMAKE_BINARY_DIR}"
        DEPENDS ${WIX_SOURCE} ${REPLACE_SCRIPT}
        COMMENT "Preprocessing WiX source file"
    )

    add_custom_command(
        OUTPUT ${WIX_OUTPUT}
        COMMAND ${WIX_EXECUTABLE} build 
        -arch ${CMAKE_VS_PLATFORM_NAME}
        -o ${WIX_OUTPUT} 
        ${WIX_PREPROCESSED}
        DEPENDS ${WIX_PREPROCESSED} BlizzardDiskMark
        COMMENT "Building MSI installer using WiX 5"
    )

    add_custom_target(WiXInstaller ALL DEPENDS ${WIX_OUTPUT})
    add_dependencies(WiXInstaller BlizzardDiskMark) # Ensure WiX runs after BlizzardDiskMark
endif()

