project(Decay)

option(BUILD_SHARED_LIBRARY "Build shared library" OFF)

#引入子文件夹
set(GLAD_PATH vendor/Glad)
set(GLFW_PATH vendor/GLFW)
set(GLM_PATH vendor/GLM)
set(IMGUI_PATH vendor/ImGui)
set(SPDLOG_PATH vendor/spdlog)
set(STB_IMAGE_PATH vendor/stb_image)

add_subdirectory(${GLAD_PATH})
add_subdirectory(${GLFW_PATH})
add_subdirectory(${IMGUI_PATH})
add_subdirectory(${SPDLOG_PATH})

#设置源文件路径
set(SRC_PATH src)

aux_source_directory(${SRC_PATH} DECAY_SOURCES)
aux_source_directory(${SPDLOG_PATH} SPDLOG_SOURCES)
aux_source_directory(${GLM_PATH} GLM_SOURCES)

add_library(Decay STATIC ${DECAY_SOURCES} ${SPDLOG_SOURCES} ${GLM_SOURCES})

#设置头文件路径
set(INCLUDE_PATH 
    ${GLAD_PATH}/include
    ${GLFW_PATH}/include
    ${IMGUI_PATH}
    ${SPDLOG_PATH}/include
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
)

#设置预编译头
target_precompile_headers(Decay PUBLIC ${SRC_PATH}/dcpch.h)

#设置编译选项
target_compile_definitions(Decay PUBLIC GLFW_INCLUDE_NONE DECAY_PLATFORM_WINDOWS DECAY_ENABLE_ASSERT)