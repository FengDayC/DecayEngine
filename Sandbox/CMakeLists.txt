project(Sandbox)

file(GLOB_RECURSE SANDBOX_SRC
    "src/*.h"
    "src/*.cpp"
)

foreach(FILE ${SANDBOX_SRC})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_executable(Sandbox ${SANDBOX_SRC})

#设置引入目录
set(INCLUDE_PATH 
    src
    ${DECAY_INCLUDE_PATH}/src 
    ${DECAY_INCLUDE_PATH}/vendor 
    ${DECAY_INCLUDE_PATH}/vendor/spdlog/include 
    ${DECAY_INCLUDE_PATH}/vendor/GLM
)

target_include_directories(Sandbox PUBLIC ${INCLUDE_PATH})

target_link_libraries(Sandbox PUBLIC Decay)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})


