project(Glad)

set(GLAD_SOURCES 
    "include/glad/glad.h" 
    "include/KHR/khrplatform.h"
    "src/glad.c"
)

add_library(Glad STATIC ${GLAD_SOURCES})

foreach(FILE ${GLAD_SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

target_include_directories(Glad PUBLIC "include")
