#include "strg_chunk.h"
#include "../main.h"
#include "../utils/utils.h"

#include <format>

std::unordered_map<u_int32_t, std::string> string_map;

std::string load_string(u_int32_t absolute_position) {
    // An additional 4 is added to skip over the length parameter
    return std::string((char*)(global_data.file_start + absolute_position + 4)); 
}

// This is only to be used for testing purposes, hence the really horrible code
void dump_strings(Chunk* string_chunk) {
    if (!compare_ident(string_chunk->ident, "STRG")) {
        throw std::invalid_argument("String chunk supplied does not have identifier `STRG`");
    }

    int num_strings = *((u_int32_t*)string_chunk->start + 2);

    u_int8_t* string_start = string_chunk->start+*((u_int32_t*)string_chunk->start + 2)*4+12;

    for (int i = 0; i < num_strings; i++) {
        int string_len = *(int*)string_start + 1; // The extra 1 is for the '\0' character
        printf("%s\n", string_start+4);
        string_start += 4 + string_len + (string_len % 4 == 0 ? 0 : 4 - string_len % 4); // Strings always start on a multiple of 4
        if (string_start - string_chunk->start > string_chunk->size) {
            throw std::out_of_range("Strings reach out of range of chunk");
        }
    }
}

void load_strings(Chunk* string_chunk) {
    if (!compare_ident(string_chunk->ident, "STRG")) {
        throw std::invalid_argument(
            std::format("String chunk supplied does not have identifier `STRG`, instead given %s", std::string(string_chunk->ident, 4))
        );
    }

    int num_strings = *((u_int32_t*)string_chunk->start + 2);

    u_int32_t* string_pointer = (u_int32_t*)string_chunk->start + 3;

    for (int i = 0; i < num_strings; i++) {
        u_int32_t address = read_safe(string_pointer, string_chunk);
        string_map[address + 4] = load_string(address);
    }
}