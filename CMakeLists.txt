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

cmake_minimum_required(VERSION 3.15)

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

# add_subdirectory(stable-diffusion.cpp)
# E:\_SourceForge\proj_qSD\thirdparty\stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86
# 设置 DLL 输出目录（可选）
# set(NAME_EXE ${CMAKE_SOURCE_DIR}/../thirdparty/stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86/sd.exe)
set(NAME_EXE ${CMAKE_SOURCE_DIR}/../qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin/Release/sd-cli.exe)
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
    file(COPY ${NAME_EXE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})# /plugins
    message("<-------- 文件存在：${NAME_EXE},已经拷贝到: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    message("<-------- 文件不存在：${NAME_EXE}")
endif()

set(NAME_EXE ${CMAKE_SOURCE_DIR}/../thirdparty/stable-diffusion__QT_5_15_6_Windows_MSVC_C_19.43.34810.0_CC_19.43.34810.0__x64_bin-cu12.9.86/stable-diffusion.dll)
if(EXISTS ${NAME_EXE})
    file(COPY ${NAME_EXE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})# /plugins
    message("<-------- 文件存在：${NAME_EXE},已经拷贝到: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    message("<-------- 文件不存在：${NAME_EXE}")
endif()


# add_subdirectory(Anydraw)    # 不带内存管理：非开源项目anydraw： 开源项目drawanything的绘画；
# add_subdirectory(drawanything)    # 不带内存管理：drawanything
add_subdirectory(stable-diffusion.cpp)
add_subdirectory(StableVerse)

add_subdirectory(StableCanvas) # 不带内存管理：开源项目full版即开源深度幻境DeepIIllusion ，对应的商业版本又名-**StableVerse（稳定幻境）**；
add_subdirectory(Anydraw)

if(STABLEVERSE_BUILD_COMMERCIAL_PLUGINS)
    add_subdirectory(StableVerse_Enhance)
    add_subdirectory(StableVerse_Activator)
endif()
# add_subdirectory(DeepIIllusion) # 开源DeepIIllusion

# add_subdirectory(StableCanvas) #带内存管理版本的：开源版本深邃的幻想ProfoundFantasy，对应的商业版本-**StableCanvas（稳定画布）**；
# add_subdirectory(ProfoundFantasy) # 开源ProfoundFantasy

# 🔥⭐StableVerse交流群⭐🔥


