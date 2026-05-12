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

# Optional: Add resource file if you have one
# qt_add_resources(${NAME} resources "resources.qrc")
