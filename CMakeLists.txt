cmake_minimum_required(VERSION 3.15...3.30)
project(GameMakerStudioEmulator VERSION 0.1.0
                  DESCRIPTION "An experimental emulator for Game Maker Studio Games"
                  LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

add_executable(gmse
    src/main.cpp
    src/runner/disassembler/disassembler.cpp
    src/chunk_handler/chunk/chunk.cpp
    src/chunk_handler/audo_chunk/audo_chunk.cpp
    src/chunk_handler/code_chunk/code_chunk.cpp
    src/chunk_handler/code_chunk/bytecode.cpp
    src/chunk_handler/gen8_chunk/gen8_chunk.cpp
    src/chunk_handler/glob_chunk/glob_chunk.cpp
    src/chunk_handler/lang_chunk/lang_chunk.cpp
    src/chunk_handler/scpt_chunk/scpt_chunk.cpp
    src/chunk_handler/strg_chunk/strg_chunk.cpp
)
target_include_directories(gmse PUBLIC src)