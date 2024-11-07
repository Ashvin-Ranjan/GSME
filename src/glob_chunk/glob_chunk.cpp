#include "glob_chunk.h"
#include "../utils/utils.h"

std::vector<u_int32_t> global_code_entry;

void load_global_entries(Chunk* global_chunk) {
    if (!compare_ident(global_chunk->ident, "GLOB")) {
        throw std::invalid_argument("Global entry chunk supplied does not have identifier `GLOB`");
    }
    
    u_int32_t* reader = (u_int32_t*)global_chunk->start + 2;

    u_int32_t length = read_safe(reader, global_chunk);

    for (int i = 0; i < length; i++) {
        global_code_entry.push_back(read_safe(reader, global_chunk));
    }
}