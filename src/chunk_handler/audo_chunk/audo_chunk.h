#ifndef GMSE_AUDO_CHUNK_H
#define GMSE_AUDO_CHUNK_H

#include "../chunk_handler.h"

#include <unordered_map>

struct Audio {
    u_int8_t* data;
    u_int32_t length;
};

extern std::unordered_map<u_int32_t, Audio> audio_map;

void free_audio_data();

void load_audio_data(Chunk* audio_chunk);

Audio load_audio(u_int32_t offset, Chunk* load_audio);

#endif