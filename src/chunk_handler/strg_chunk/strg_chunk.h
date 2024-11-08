#ifndef GMSE_STRING_CHUNK_H
#define GMSE_STRING_CHUNK_H

#include "../chunk/chunk.h"

#include <unordered_map>

extern std::unordered_map<u_int32_t, std::string> string_map;

void dump_strings(Chunk* string_chunk);

void load_strings(Chunk* string_chunk);

#endif