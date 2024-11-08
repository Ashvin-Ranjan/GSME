#ifndef GMSE_CODE_CHUNK_H
#define GMSE_CODE_CHUNK_H

#include "../chunk/chunk.h"

struct GameCode {
    u_int32_t name_pointer;
    u_int32_t length;
    u_int32_t bytecode_pointer;
    u_int16_t locals_count;
    u_int16_t argument_count;
    u_int8_t flags;
};

void load_game_codes(Chunk* code_chunk);

GameCode load_code(u_int32_t offset, Chunk* code_chunk);

#endif