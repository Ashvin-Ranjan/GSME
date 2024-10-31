cmake_minimum_required(VERSION 3.15...3.30)
project(GameMakerStudioEmulator VERSION 0.1.0
                  DESCRIPTION "An experimental emulator for Game Maker Studio Games"
                  LANGUAGES CXX)

add_executable(gmse src/main.cpp src/chunk.cpp)
target_include_directories(gmse PUBLIC src)
