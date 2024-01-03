set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)

project(DecayEngine)

# 设置build路径
# set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

#源文件路径
set(DECAY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Decay)
set(SANDBOX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)

#头文件路径
set(DECAY_INCLUDE_PATH ${DECAY_PATH})

add_subdirectory(Decay)
add_subdirectory(Sandbox)

# 设置Sandbox为启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)