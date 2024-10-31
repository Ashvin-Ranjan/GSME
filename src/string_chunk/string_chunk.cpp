#include "string_chunk.h"

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