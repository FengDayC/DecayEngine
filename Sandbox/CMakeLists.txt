project(Sandbox)

aux_source_directory(src SANDBOX_SRC)

add_executable(Sandbox ${SANDBOX_SRC})

target_include_directories(Sandbox PUBLIC ${DECAY_INCLUDE_PATH})

target_link_libraries(Sandbox Decay)