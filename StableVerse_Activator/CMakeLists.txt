cmake_minimum_required(VERSION 3.5)

set(NAME StableVerse_Activator)# LicenseSystem_ini_deepseek)
project(${NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_standard_project_setup()
endif()

set(SOURCES
    ./main.cpp
    ./MainWindow.cpp
    ./LicenseManager.cpp
    ./MacAddressHelper.cpp MainWindow.ui
)

set(HEADERS
    ./MainWindow.h
    ./LicenseManager.h
    ./MacAddressHelper.h
)

add_executable(${NAME} ${SOURCES} ${HEADERS}
    MyDialog.h
    LicenseByUID.h)

target_include_directories(${NAME} PRIVATE include)

target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

if(WIN32)
    target_link_libraries(${NAME} PRIVATE iphlpapi)
endif()

if(STABLEVERSE_BUILD_COMMERCIAL_PLUGINS)
    set(_sv_plugin_api "${CMAKE_CURRENT_SOURCE_DIR}/../StableVerse/include/common")
    add_library(StableVerse_ActivatorPlugin SHARED activator_plugin.cpp)
    target_include_directories(StableVerse_ActivatorPlugin PRIVATE ${_sv_plugin_api})
    target_link_libraries(StableVerse_ActivatorPlugin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    set_target_properties(StableVerse_ActivatorPlugin PROPERTIES PREFIX "")
    add_dependencies(StableVerse_ActivatorPlugin StableVerse)
    add_custom_command(
        TARGET StableVerse_ActivatorPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:StableVerse>/plugins"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:StableVerse_ActivatorPlugin>
                "$<TARGET_FILE_DIR:StableVerse>/plugins")
endif()

# Optional: Add resource file if you have one
# qt_add_resources(${NAME} resources "resources.qrc")
