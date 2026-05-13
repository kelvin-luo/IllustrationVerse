# /*
#     Copyright (C) 2021  kelvin-luo

#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU Affero General Public License as published
#     by the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.

#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU Affero General Public License for more details.

#     You should have received a copy of the GNU Affero General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#     My Github homepage: https://github.com/kelvin-luo
# */

cmake_minimum_required(VERSION 3.16)

# kelvin-luo
set(NAME qSD)
project(${NAME} VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# //------------------------------------------//
include(cmake_Kelvin/ProjectSetting.cmake)
# //------------------------------------------//

option(STABLEVERSE_BUILD_COMMERCIAL_PLUGINS
       "Build optional commercial plugin DLLs into StableVerse.exe/plugins" OFF)

# E:\_SourceForge\proj_qSD\thirdparty\stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86
# 设置 DLL 输出目录（可选）
# set(NAME_EXE ${CMAKE_SOURCE_DIR}/../thirdparty/stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86/sd.exe)
set(NAME_EXE ${CMAKE_SOURCE_DIR}/../build-msvc/bin/Release/sd-cli.exe)
# set_target_properties(${NAME_EXE} PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
#     RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
# )
# # 指定目标目录（项目根目录下的 bin 目录）
# set(DESTINATION_DIR ${EXECUTABLE_OUTPUT_PATH}/)#plugins
# # 创建目标目录（如果不存在）
# file(MAKE_DIRECTORY ${DESTINATION_DIR})
# # 配置 DLL 拷贝命令
# add_custom_command(
#     TARGET ${NAME_EXE}
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#         $<TARGET_FILE:${NAME_EXE}>
#         ${DESTINATION_DIR}
#     COMMENT "Copying DLL to ${DESTINATION_DIR}"
# )

# 使用file COPY命令拷贝文件
if(EXISTS ${NAME_EXE})
    file(COPY ${NAME_EXE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)# /plugins
    message("<-------- 文件存在：${NAME_EXE},已经拷贝到: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
else()
    message("<-------- 文件不存在：${NAME_EXE}")
endif()

# set(NAME_EXE ${CMAKE_SOURCE_DIR}/../thirdparty/stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86/stable-diffusion.dll)
# if(EXISTS ${NAME_EXE})
#     file(COPY ${NAME_EXE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})# /plugins
#     message("<-------- 文件存在：${NAME_EXE},已经拷贝到: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# else()
#     message("<-------- 文件不存在：${NAME_EXE}")
# endif()


# stable-diffusion.cpp：CMake 拉取 https://github.com/leejet/stable-diffusion.cpp （含 ggml 子模块），不再使用本地子模块目录
include(FetchContent)
set(SD_BUILD_EXAMPLES OFF CACHE BOOL "sd: build examples" FORCE)
FetchContent_Declare(
    stable_diffusion_cpp
    GIT_REPOSITORY https://github.com/leejet/stable-diffusion.cpp.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    # GIT_SUBMODULES "ggml"
    GIT_SUBMODULES_RECURSE TRUE
)
FetchContent_MakeAvailable(stable_diffusion_cpp)

add_subdirectory(StableVerse)

add_subdirectory(canvas)   # canvas 插件库 / 独立程序（原 StableCanvas）
add_subdirectory(anydraw)  # anydraw 插件库 / 独立程序（原 Anydraw）

if(STABLEVERSE_BUILD_COMMERCIAL_PLUGINS)
    add_subdirectory(enhance)     # enhance 插件库（原 StableVerse_Enhance）
    add_subdirectory(activator)    # activator 插件库（原 StableVerse_Activator）
endif()
# add_subdirectory(DeepIIllusion) # 开源DeepIIllusion

# add_subdirectory(canvas) # 带内存管理版本：ProfoundFantasy 等
# add_subdirectory(ProfoundFantasy) # 开源ProfoundFantasy

# 🔥⭐StableVerse交流群⭐🔥


