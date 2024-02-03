project(Decay)

option(BUILD_SHARED_LIBRARY "Build shared library" OFF)

#引入子文件夹
set(GLAD_PATH vendor/Glad)
set(GLFW_PATH vendor/GLFW)
set(GLM_PATH vendor/GLM)
set(IMGUI_PATH vendor/ImGui)
set(SPDLOG_PATH vendor/spdlog)
set(STB_IMAGE_PATH vendor/stb_image)
set(ASSIMP_PATH vendor/assimp)
set(ENTT_PATH vendor/entt)

set(ASSIMP_INSTALL OFF)

add_subdirectory(${GLAD_PATH})
add_subdirectory(${GLFW_PATH})
add_subdirectory(${IMGUI_PATH})
add_subdirectory(${SPDLOG_PATH})
add_subdirectory(${ASSIMP_PATH})
add_subdirectory(${ENTT_PATH})

#设置源文件路径
set(SRC_PATH src)

#设置源文件
file(GLOB_RECURSE DECAY_SOURCES
    ${SRC_PATH}/*.cpp
    ${SRC_PATH}/*.h
    ${SRC_PATH}/*.hpp
    ${SRC_PATH}/*.c
    ${SRC_PATH}/*.cc
    ${SRC_PATH}/*.hh
    ${SRC_PATH}/*.inl
)
file(GLOB_RECURSE STB_IMAGE_SOURCES
    ${STB_IMAGE_PATH}/*.cpp
    ${STB_IMAGE_PATH}/*.h
    ${STB_IMAGE_PATH}/*.hpp
    ${STB_IMAGE_PATH}/*.c
    ${STB_IMAGE_PATH}/*.cc
    ${STB_IMAGE_PATH}/*.hh
    ${STB_IMAGE_PATH}/*.inl
)
file(GLOB_RECURSE GLM_SOURCES
    ${GLM_PATH}/*.hpp
    ${GLM_PATH}/*.inl
)
file(GLOB_RECURSE ENTT_SOURCES
    ${ENTT_PATH}/single_include/*.hpp
)

#组织VS代码结构
foreach(FILE ${DECAY_SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
foreach(FILE ${STB_IMAGE_SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
foreach(FILE ${GLM_SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
foreach(FILE ${ENTT_SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(Decay STATIC ${DECAY_SOURCES} ${STB_IMAGE_SOURCES} ${GLM_SOURCES} ${ENTT_SOURCES})

#设置头文件路径
set(INCLUDE_PATH 
    ${GLAD_PATH}/include
    ${GLFW_PATH}/include
    ${IMGUI_PATH}
    ${SPDLOG_PATH}/include
    ${ASSIMP_PATH}/include
    ${ENTT_PATH}/single_include
    ${STB_IMAGE_PATH}
    ${GLM_PATH}
    ${SRC_PATH}
    ${SRC_PATH}/Decay
)

target_include_directories(Decay PUBLIC ${INCLUDE_PATH})

#设置链接目标
target_link_libraries(Decay PUBLIC
    Glad
    glfw
    ImGui
    spdlog
    opengl32.lib
    assimp
)

#设置预编译头
target_precompile_headers(Decay PUBLIC ${SRC_PATH}/dcpch.h)

#设置预编译选项
target_compile_definitions(Decay PUBLIC GLFW_INCLUDE_NONE DECAY_PLATFORM_WINDOWS DECAY_ENABLE_ASSERTS NOMINMAX)
