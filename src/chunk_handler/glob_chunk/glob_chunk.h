#ifndef GMSE_GLOB_CHUNK_H
#define GMSE_GLOB_CHUNK_H

#include "../chunk_handler.h"

extern std::vector<u_int32_t> global_code_entry;

void load_global_entries(Chunk* global_chunk);

#endif