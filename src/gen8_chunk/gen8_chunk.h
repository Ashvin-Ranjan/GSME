#ifndef GMSE_GEN8_CHUNK_H
#define GMSE_GEN8_CHUNK_H

#include "../chunk/chunk.h"

struct GameInfo {
    bool disable_debug;
    u_int8_t format_id;
};

static GameInfo game_info;

void load_game_info(Chunk* gen8_chunk);

#endif