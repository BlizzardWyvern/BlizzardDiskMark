set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/res/DiskMark.rc")

add_executable(BlizzardDiskMark
    application.qrc
    DiskMark.cpp 
    DiskBench.cpp 
    DiskMarkDlg.cpp
    # SettingsDlg.cpp
    ${app_icon_resource_windows}
)

qt_add_qml_module(BlizzardDiskMark
    URI BlizzardDiskMark
    QML_FILES 
        DiskMarkDlg.qml
        AboutDlg.qml
    SOURCES 
        DiskMarkDlg.cpp 
        DiskMarkDlg.h
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
    Qt6::WebView
    BlizzardIglooplugin
)
target_compile_definitions(BlizzardDiskMark PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

set_target_properties(BlizzardDiskMark PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        add_custom_command(TARGET BlizzardDiskMark POST_BUILD
            COMMAND ${Qt6_DIR}/../../../bin/windeployqt.exe 
                --release --no-translations
                --qmldir ${CMAKE_SOURCE_DIR}/src/app 
                $<TARGET_FILE:BlizzardDiskMark>
            COMMENT "Running windeployqt on BlizzardDiskMark executable with QML directory"
        )

        # Download fio msi installer dependent on the architecture
        set(FIO_INSTALLER_URL "https://github.com/axboe/fio/releases/download/fio-3.39/fio-3.39-${CMAKE_VS_PLATFORM_NAME}.msi")
        set(FIO_INSTALLER ${CMAKE_BINARY_DIR}/installer/fio-${CMAKE_VS_PLATFORM_NAME}.msi)

        file(DOWNLOAD ${FIO_INSTALLER_URL} ${FIO_INSTALLER}
            EXPECTED_HASH SHA256=49be53fb6b9517ce4fc5e26136d7c981df84daa31dd50db66ac3bbb5cb7be63a
            SHOW_PROGRESS
        )

        set(VC_REDIST ${CMAKE_BINARY_DIR}/installer/vc_redist.${CMAKE_VS_PLATFORM_NAME}.exe)
        if (EXISTS ${CMAKE_BINARY_DIR}/Release/vc_redist.${CMAKE_VS_PLATFORM_NAME}.exe)
            # Move vc_redist installer to the installer directory
            file(COPY ${CMAKE_BINARY_DIR}/Release/vc_redist.${CMAKE_VS_PLATFORM_NAME}.exe DESTINATION ${CMAKE_BINARY_DIR}/installer)
            file(REMOVE ${CMAKE_BINARY_DIR}/Release/vc_redist.${CMAKE_VS_PLATFORM_NAME}.exe)
        endif()

        find_program(WIX_EXECUTABLE wix.exe REQUIRED)

        # WiX source and output files for BlizzardDiskMark
        set(WIX_SOURCE_BDM ${CMAKE_SOURCE_DIR}/installer/BlizzardDiskMark.wxs)
        set(WIX_OUTPUT_BDM ${CMAKE_BINARY_DIR}/installer/BlizzardDiskMarkStandalone.msi)

        # WiX source and output files for ChainInstaller
        set(WIX_SOURCE_CHAIN ${CMAKE_SOURCE_DIR}/installer/ChainInstaller.wxs)
        set(WIX_OUTPUT_CHAIN ${CMAKE_BINARY_DIR}/installer/BlizzardDiskMark.exe)

        # Build the MSI installers
        add_custom_command(
            OUTPUT ${WIX_OUTPUT_BDM}
            COMMAND ${WIX_EXECUTABLE} build 
            -arch ${CMAKE_VS_PLATFORM_NAME}
            -d SourceDir=${CMAKE_SOURCE_DIR}
            -d BinaryDir=${CMAKE_BINARY_DIR}
            -pdbtype none
            -o ${WIX_OUTPUT_BDM} 
            ${WIX_SOURCE_BDM}
            DEPENDS BlizzardDiskMark
            COMMENT "Building MSI installer"
        )

        add_custom_command(
            OUTPUT ${WIX_OUTPUT_CHAIN}
            COMMAND ${WIX_EXECUTABLE} build 
            -arch ${CMAKE_VS_PLATFORM_NAME}
            -d Standalone=${WIX_OUTPUT_BDM}
            -d FioInstaller=${FIO_INSTALLER}
            -d VcRedist=${VC_REDIST}
            -d SourceDir=${CMAKE_SOURCE_DIR}
            -d BinaryDir=${CMAKE_BINARY_DIR}
            -pdbtype none
            -ext WixToolset.BootstrapperApplications.wixext
            -o ${WIX_OUTPUT_CHAIN} 
            ${WIX_SOURCE_CHAIN}
            DEPENDS BlizzardDiskMark
            COMMENT "Building bundle installer"
        )

        add_custom_target(WiXInstaller_BDM ALL DEPENDS ${WIX_OUTPUT_BDM})
        add_custom_target(WiXInstaller_CHAIN ALL DEPENDS ${WIX_OUTPUT_CHAIN})

        add_dependencies(WiXInstaller_BDM BlizzardDiskMark)
        add_dependencies(WiXInstaller_CHAIN WiXInstaller_BDM)
    endif()
endif()

