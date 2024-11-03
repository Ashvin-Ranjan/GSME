cmake_minimum_required(VERSION 3.15...3.30)
project(GameMakerStudioEmulator VERSION 0.1.0
                  DESCRIPTION "An experimental emulator for Game Maker Studio Games"
                  LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

add_executable(gmse src/main.cpp src/chunk/chunk.cpp src/string_chunk/string_chunk.cpp)
target_include_directories(gmse PUBLIC src)