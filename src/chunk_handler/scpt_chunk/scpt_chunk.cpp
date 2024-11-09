#include "../chunk_handler.h"
#include "../../main.h"
#include "../../utils/utils.h"

std::unordered_map<u_int32_t, Script> script_map;

void load_script_data(Chunk* script_chunk) {
    if (!compare_ident(script_chunk->ident, "SCPT")) {
        throw std::invalid_argument("Script chunk supplied does not have identifier `SCPT`");
    }

    u_int32_t* reader = (u_int32_t*)script_chunk->start + 2;

    u_int32_t length = read_safe(reader, script_chunk);

    for (int i = 0; i < length; i++) {
        u_int32_t loc = read_safe(reader, script_chunk);
        printf("%i, %x\n", i, loc);
        script_map[loc] = load_script(loc, script_chunk);
    }
}


Script load_script(u_int32_t offset, Chunk* script_chunk) {
    if (!compare_ident(script_chunk->ident, "SCPT")) {
        throw std::invalid_argument("Script chunk supplied does not have identifier `SCPT`");
    }

    u_int32_t* reader = (u_int32_t*)(global_data.file_start + offset);
    Script s;
    s.name_pointer = read_safe(reader, script_chunk);
    s.code_id = read_safe(reader, script_chunk);
    s.constructor = !!(s.code_id >> 31);
    s.code_id &= 0x7FFFFFFF;

    return s;
}