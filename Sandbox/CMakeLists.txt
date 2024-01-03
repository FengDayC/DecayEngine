project(Sandbox)

aux_source_directory(src SANDBOX_SRC)

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