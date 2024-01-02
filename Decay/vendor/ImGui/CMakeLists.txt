project(ImGui)

aux_source_directory(. ImGui_SRCS)

add_library(ImGui STATIC ${ImGui_SRCS})