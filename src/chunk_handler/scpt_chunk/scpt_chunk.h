#ifndef GMSE_SCPT_CHUNK_H
#define GMSE_SCPT_CHUNK_H

#include "../chunk_handler.h"

#include <unordered_map>

struct Script {
    u_int32_t name_pointer;
    u_int32_t code_id;
    bool constructor;
};

extern std::unordered_map<u_int32_t, Script> script_map;

void load_script_data(Chunk* script_chunk);

Script load_script(u_int32_t offset, Chunk* script_chunk);

#endif