set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)

project(DecayEngine)

#源文件路径
set(DECAY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Decay)
set(SANDBOX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)

#头文件路径
set(DECAY_INCLUDE_PATH ${DECAY_PATH}/src)

message("DecayEngine: ${DECAY_PATH}")
message("SandBox: ${SANDBOX_PATH}")

add_subdirectory(Decay)
add_subdirectory(Sandbox)
