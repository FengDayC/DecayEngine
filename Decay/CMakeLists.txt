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
add_subdirectory(${GLM_PATH})
add_subdirectory(${IMGUI_PATH})
add_subdirectory(${SPDLOG_PATH})
add_subdirectory(${STB_IMAGE_PATH})

#设置源文件路径
set(SRC_PATH src)

aux_source_directory(${SRC_PATH} SOURCES)

add_library(Decay STATIC ${SOURCES})

#设置头文件路径
set(INCLUDE_PATH 
    ${GLAD_PATH}/include
    ${GLFW_PATH}/include
    ${GLM_PATH}
    ${IMGUI_PATH}
    ${SPDLOG_PATH}/include
    ${STB_IMAGE_PATH}
    ${SRC_PATH}
)

target_include_directories(Decay PUBLIC ${INCLUDE_PATH})

#设置链接目标
target_link_libraries(Decay PUBLIC
    Glad
    GLFW
    glm
    ImGui
    spdlog
    stb_image
)

#设置预编译头
target_precompile_headers(Decay PUBLIC ${SRC_PATH}/dcpch.h)
