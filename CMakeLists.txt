cmake_minimum_required(VERSION 3.10)
project(WavefrontTexturePacker)

set(CMAKE_CXX_STANDARD 17)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(WavefrontTexturePacker src/main.cpp library/stb_image.h)