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

# Nested ggml ExternalProject try-compiles hit MSBuild FileTracker FTK1011 on some paths; VS
# generators honor this global for all .vcxproj (including custom build steps).
if(WIN32 AND CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_VS_GLOBALS "TrackFileAccess=false")
endif()

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
# ggml-vulkan 在极深的 ExternalProject 里跑 TryCompile；路径过长时 MSBuild FileTracker 报 FTK1011。
# 已有 CMakeCache 里若写过 FETCHCONTENT_BASE_DIR，普通 set(CACHE) 不会覆盖，故默认用 FORCE 指到短路径。
option(ILLUSTRATIONVERSE_FETCHCONTENT_STAY_IN_BUILD_DIR
       "Keep FetchContent under build/_deps (Windows: 易触发 vulkan-shaders-gen 的 FTK1011)" OFF)
if(WIN32 AND NOT ILLUSTRATIONVERSE_FETCHCONTENT_STAY_IN_BUILD_DIR)
    file(TO_CMAKE_PATH "$ENV{LOCALAPPDATA}/IllustrationVerse-fetchcontent" _iv_fetchcontent_base)
    set(FETCHCONTENT_BASE_DIR "${_iv_fetchcontent_base}"
        CACHE PATH "FetchContent 根目录（短路径，减轻 ggml Vulkan 嵌套配置的 FTK1011 / MAX_PATH）"
        FORCE)
    file(MAKE_DIRECTORY "${FETCHCONTENT_BASE_DIR}")
endif()
set(SD_BUILD_EXAMPLES OFF CACHE BOOL "sd: build examples" FORCE)
FetchContent_Declare(
    stable_diffusion_cpp
    GIT_REPOSITORY https://github.com/leejet/stable-diffusion.cpp.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    # GIT_SUBMODULES "ggml"
    GIT_SUBMODULES_RECURSE TRUE
    # 本地修补 vulkan-shaders/CMakeLists.txt 后避免每次 configure 执行 git pull 因脏工作区失败
    UPDATE_DISCONNECTED TRUE
)
FetchContent_MakeAvailable(stable_diffusion_cpp)

set(_iv_vk_shaders_cmake "${stable_diffusion_cpp_SOURCE_DIR}/ggml/src/ggml-vulkan/vulkan-shaders/CMakeLists.txt")
set(_iv_ggml_vulkan_cmake "${stable_diffusion_cpp_SOURCE_DIR}/ggml/src/ggml-vulkan/CMakeLists.txt")
if(EXISTS "${_iv_ggml_vulkan_cmake}")
    file(READ "${_iv_ggml_vulkan_cmake}" _iv_ggml_vk_undo)
    if(_iv_ggml_vk_undo MATCHES "-DCMAKE_VS_GLOBALS=TrackFileAccess=false -DCMAKE_INSTALL_PREFIX=")
        string(REPLACE "-DCMAKE_VS_GLOBALS=TrackFileAccess=false -DCMAKE_INSTALL_PREFIX=" "-DCMAKE_INSTALL_PREFIX="
            _iv_ggml_vk_undo "${_iv_ggml_vk_undo}")
        file(WRITE "${_iv_ggml_vulkan_cmake}" "${_iv_ggml_vk_undo}")
    endif()
endif()

find_program(_iv_ninja NAMES ninja ninja.exe)
if(_iv_ninja)
    file(TO_CMAKE_PATH "${_iv_ninja}" _iv_ninja_cmake)
    if(EXISTS "${_iv_ggml_vulkan_cmake}")
        file(READ "${_iv_ggml_vulkan_cmake}" _iv_ggml_vk_raw)
        string(FIND "${_iv_ggml_vk_raw}" "IllustrationVerse: Ninja for vulkan-shaders-gen" _iv_ninja_marker)
        if(_iv_ninja_marker EQUAL -1)
            if(EXISTS "${_iv_vk_shaders_cmake}")
                file(READ "${_iv_vk_shaders_cmake}" _iv_vks_raw)
                string(REPLACE [[cmake_minimum_required(VERSION 3.19)
# IllustrationVerse: FT workaround — MSBuild FileTracker FTK1011 on try-compile .tlog (must precede project()).
if(WIN32 AND CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_VS_GLOBALS "TrackFileAccess=false")
endif()
project("vulkan-shaders-gen" C CXX)]]
                    [[cmake_minimum_required(VERSION 3.19)
project("vulkan-shaders-gen" C CXX)]]
                    _iv_vks_raw "${_iv_vks_raw}")
                file(WRITE "${_iv_vk_shaders_cmake}" "${_iv_vks_raw}")
            endif()
            set(_iv_ep_needle "        SOURCE_DIR \${CMAKE_CURRENT_SOURCE_DIR}/vulkan-shaders\n        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=\${CMAKE_BINARY_DIR}/\$<CONFIG>")
            set(_iv_ep_replace "        SOURCE_DIR \${CMAKE_CURRENT_SOURCE_DIR}/vulkan-shaders\n        # IllustrationVerse: Ninja for vulkan-shaders-gen (avoid MSVC FileTracker FTK1011)\n        CMAKE_GENERATOR Ninja\n        CMAKE_MAKE_PROGRAM \"${_iv_ninja_cmake}\"\n        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=\${CMAKE_BINARY_DIR}/\$<CONFIG>")
            string(REPLACE "${_iv_ep_needle}" "${_iv_ep_replace}" _iv_ggml_vk_raw "${_iv_ggml_vk_raw}")
            string(FIND "${_iv_ggml_vk_raw}" "IllustrationVerse: Ninja for vulkan-shaders-gen" _iv_ninja_verify)
            if(_iv_ninja_verify EQUAL -1)
                message(WARNING "Could not patch ggml-vulkan ExternalProject for Ninja; vulkan-shaders-gen may hit FTK1011.")
            else()
                file(WRITE "${_iv_ggml_vulkan_cmake}" "${_iv_ggml_vk_raw}")
                message(STATUS "vulkan-shaders-gen ExternalProject uses Ninja: ${_iv_ninja_cmake}")
            endif()
        endif()
    endif()
elseif(WIN32 AND EXISTS "${_iv_vk_shaders_cmake}")
    file(READ "${_iv_vk_shaders_cmake}" _iv_vks_raw)
    string(FIND "${_iv_vks_raw}" "IllustrationVerse: FT workaround" _iv_vks_marker)
    if(_iv_vks_marker EQUAL -1)
        string(REPLACE [[cmake_minimum_required(VERSION 3.19)
project("vulkan-shaders-gen" C CXX)]]
            [[cmake_minimum_required(VERSION 3.19)
# IllustrationVerse: FT workaround — install Ninja for a reliable fix (PATH: ninja.exe).
if(WIN32 AND CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_VS_GLOBALS "TrackFileAccess=false")
endif()
project("vulkan-shaders-gen" C CXX)]]
            _iv_vks_raw "${_iv_vks_raw}")
        file(WRITE "${_iv_vk_shaders_cmake}" "${_iv_vks_raw}")
        message(STATUS "Patched ggml vulkan-shaders/CMakeLists.txt (ninja not found): CMAKE_VS_GLOBALS before nested project()")
    endif()
endif()

set(_iv_vkgen_build "${stable_diffusion_cpp_BINARY_DIR}/ggml/src/ggml-vulkan/vulkan-shaders-gen-prefix/src/vulkan-shaders-gen-build")
if(EXISTS "${_iv_ggml_vulkan_cmake}" AND EXISTS "${_iv_vkgen_build}/CMakeCache.txt")
    file(READ "${_iv_ggml_vulkan_cmake}" _iv_ggml_vk_chk)
    file(READ "${_iv_vkgen_build}/CMakeCache.txt" _iv_vkgen_cache)
    if(_iv_ggml_vk_chk MATCHES "IllustrationVerse: Ninja for vulkan-shaders-gen"
       AND _iv_vkgen_cache MATCHES "CMAKE_GENERATOR:INTERNAL=Visual Studio")
        file(REMOVE_RECURSE "${_iv_vkgen_build}")
        message(STATUS "Removed stale vulkan-shaders-gen-build (nested project will reconfigure with Ninja)")
    endif()
endif()

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


