cmake_minimum_required(VERSION 3.10)
project(WavefrontTexturePacker)

set(CMAKE_CXX_STANDARD 17)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(WavefrontTexturePacker src/main.cpp library/stb_image.h src/block.cpp src/block.h src/node.cpp src/node.h library/stb_image_write.h src/image.cpp src/image.h src/texture_util.cpp src/texture_util.h src/string_util.cpp src/string_util.h src/block_packer.cpp src/block_packer.h src/wavefront_parser.cpp src/wavefront_parser.h src/Options.cpp src/Options.h)