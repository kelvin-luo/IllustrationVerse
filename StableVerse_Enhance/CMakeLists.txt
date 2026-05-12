# 插件1：日志增强
set(NAME StableVerse_Enhance)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)

if(QT_VERSION_MAJOR MATCHES "5")
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets  OpenGL Network  REQUIRED)
else()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent Multimedia MultimediaWidgets Core5Compat  OpenGL OpenGLWidgets Network REQUIRED)
endif()

include_directories(gui . activation common core ../../thirdparty)
file(GLOB_RECURSE soruce ./*.cpp *.h *.ui *.qrc *.ts)


add_library(${NAME} SHARED license.h ${soruce} )

# target_link_libraries(${NAME} Qt${QT_VERSION_MAJOR}::Core)

if(QT_VERSION_MAJOR MATCHES "5")
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::Network -lopengl32)
else()
    target_link_libraries(${NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core5Compat Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::Network)
endif()

# 设置插件属性
set_target_properties(${NAME} PROPERTIES
    PREFIX ""
    # SUFFIX ".so"  # Linux/MacOS
    SUFFIX ".dll"  # Windows
)

# 指定目标目录（项目根目录下的 bin 目录）
set(DESTINATION_DIR ${EXECUTABLE_OUTPUT_PATH}/plugins)
# 创建目标目录（如果不存在）
file(MAKE_DIRECTORY ${DESTINATION_DIR})
# 配置 DLL 拷贝命令
add_custom_command(
    TARGET  ${NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${NAME}>
        ${DESTINATION_DIR}
    COMMENT "Copying DLL to ${DESTINATION_DIR}"
)
# 使用file COPY命令拷贝文件
if(EXISTS ${OUTPUT_DIR_KENT}/StableVerse_Enhanced.dll)
    file(COPY ${OUTPUT_DIR_KENT}/StableVerse_Enhanced.dll
        DESTINATION ${OUTPUT_DIR_KENT}/plugins)
else()
    message("plugin not existd: ${OUTPUT_DIR_KENT}/${NAME} ")
endif()
# if(EXISTS    ${NAME})
#     file(COPY    ${NAME}
#         DESTINATION ${OUTPUT_DIR_KENT}/plugins)
# else()
#     message("plugin not existd: TARGET  ${NAME} ")
# endif()

# 安装插件到主程序目录的plugins子目录
install(TARGETS ${NAME} ${NAME2}
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/plugins
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/plugins
)
    
