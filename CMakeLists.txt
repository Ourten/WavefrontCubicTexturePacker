cmake_minimum_required(VERSION 3.10)
project(WavefrontTexturePacker)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(WavefrontTexturePacker src/main.cpp library/stb_image.h src/block.cpp include/block.h src/node.cpp include/node.h library/stb_image_write.h src/image.cpp include/image.h src/texture_util.cpp include/texture_util.h src/string_util.cpp include/string_util.h src/block_packer.cpp include/block_packer.h src/wavefront_parser.cpp include/wavefront_parser.h src/options.cpp include/options.h)