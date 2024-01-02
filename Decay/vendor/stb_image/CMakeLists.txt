project(stb_image)

add_library(stb_image STATIC stb_image.cpp stb_image.h)

target_include_directories(stb_image PUBLIC ${DECAY_INCLUDE_PATH})