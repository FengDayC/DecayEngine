project(ImGui)

file(GLOB ImGui_SRCS
    "*.cpp"
    "*.h"
)

foreach(FILE ${ImGui_SRCS})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(ImGui STATIC ${ImGui_SRCS})