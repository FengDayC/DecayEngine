file(GLOB_RECURSE ASSETS_FILES
    Shaders/*
    Models/*
    Textures/*)

foreach(FILE ${ASSETS_FILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_custom_target(Assets SOURCES ${ASSETS_FILES})