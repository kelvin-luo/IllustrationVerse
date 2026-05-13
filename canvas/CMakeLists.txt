cmake_minimum_required(VERSION 3.16)

set(NAME canvas)
project(${NAME} LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)

if(QT_VERSION_MAJOR MATCHES "5")
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets  OpenGL   REQUIRED)
else()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets Core5Compat  OpenGL OpenGLWidgets  REQUIRED)
endif()

set(trage_runtime_output_dir ${OUTPUT_DIR_KENT})
set(EXECUTABLE_OUTPUT_PATH "${trage_runtime_output_dir}") # qtcreator + msvc 可执行文件的输出目录
set(CMAKE_BINARY_DIR "${trage_runtime_output_dir}")             # visual studio 2022 可执行的输出目录
file(MAKE_DIRECTORY ${trage_runtime_output_dir})                      # 创建输出目录


#***************************************************通用参数的定义 开始**********************************************
# get kit architecture bit
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(architecture_bit "x86")
    set(build_x64bit false)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(architecture_bit "x64")
    set(build_x64bit true)
endif()

# 设置变量 qt/ssl/lupdate/lrelease 在不同编译器下的环境和版本下的 path
get_target_property(QtCore_location Qt${QT_VERSION_MAJOR}::Core LOCATION)
get_filename_component(qt_binray_dir ${QtCore_location} DIRECTORY)
message("Qt installation directory qt_binray_dir: ${qt_binray_dir}")            # C:/Qt/6.7.3/msvc2022_64/bin

set(lupdate_path "${qt_binray_dir}/lupdate")
set(lrelease_path "${qt_binray_dir}/lrelease")

message("--->architecture_bit:" ${architecture_bit}  "  build_x64bit:" ${build_x64bit}  "  ssl_dir:" ${ssl_dir} "  HOME_DIR:" ${HOME_DIR} "  env_os:" ${env_os})
message("lupdate_path:" ${lupdate_path})
message("lrelease_path:" ${lrelease_path})
message("EXECUTABLE_OUTPUT_PATH:" ${EXECUTABLE_OUTPUT_PATH})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})

add_executable(${NAME}
    main.cpp
    # mainwindow.cpp
    # mainwindow.h
    # mainwindow.ui
    # resource.qrc
    # openglimagewidget.h openglimagewidget.cpp
    # myqgraphicsview.h myqgraphicsview.cpp
)

if(QT_VERSION_MAJOR MATCHES "5")
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::OpenGL -lopengl32)
else()
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core5Compat Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets )
endif()

if(0)
# # 确保可执行文件与imageProc.exe在同一目录
# add_custom_command(TARGET ${NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         $<TARGET_FILE:imageProc>
#         $<TARGET_FILE_DIR:${NAME}>
#     COMMENT "Copying sd.exe to output directory"
# )
endif()

#***************************************************************************************
if(0)
set(windeployqt "${qt_binray_dir}/windeployqt.exe")
add_custom_command(TARGET ${NAME} POST_BUILD COMMAND "${windeployqt}" "${EXECUTABLE_OUTPUT_PATH}/${NAME}.exe" --no-translations)
message("--->windeployqt(or mac/linux): ${windeployqt}")
endif()

if(STABLEVERSE_BUILD_COMMERCIAL_PLUGINS)
    set(_sv_plugin_api "${CMAKE_CURRENT_SOURCE_DIR}/../StableVerse/include/common")
    add_library(canvas_plugin SHARED canvas_plugin.cpp)
    target_include_directories(canvas_plugin PRIVATE ${_sv_plugin_api})
    target_link_libraries(canvas_plugin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    set_target_properties(canvas_plugin PROPERTIES PREFIX "")
    add_dependencies(canvas_plugin StableVerse)
    add_custom_command(
        TARGET canvas_plugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:StableVerse>/plugins"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:canvas_plugin>
                "$<TARGET_FILE_DIR:StableVerse>/plugins")
endif()
