# Commercial add-on: loaded at runtime from <StableVerse.exe dir>/plugins
set(NAME StableVerse_Enhance)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)

if(QT_VERSION_MAJOR MATCHES "5")
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets OpenGL Network REQUIRED)
else()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets Core5Compat OpenGL OpenGLWidgets Network REQUIRED)
endif()

set(_sv_root "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(${NAME} SHARED enhance_plugin.cpp license.h)

target_include_directories(${NAME} PRIVATE ${_sv_root}/StableVerse/include/common ${_sv_root}/StableVerse/include .)

if(QT_VERSION_MAJOR MATCHES "5")
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::Network -lopengl32)
else()
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core5Compat Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::Network)
endif()

set_target_properties(${NAME} PROPERTIES PREFIX "")

add_dependencies(${NAME} StableVerse)
add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:StableVerse>/plugins"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${NAME}> "$<TARGET_FILE_DIR:StableVerse>/plugins"
    COMMENT "Copy ${NAME} next to StableVerse.exe/plugins"
)
