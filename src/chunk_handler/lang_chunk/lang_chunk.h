#ifndef GMSE_LANG_CHUNK_H
#define GMSE_LANG_CHUNK_H

#include "../chunk_handler.h"

struct Language {
    u_int32_t name_pointer;
    u_int32_t region_pointer;
    std::vector<u_int32_t> entry_pointers;
};

void load_languages(Chunk* lang_chunk);

Language load_language(u_int32_t*& reader, Chunk* lang_chunk, u_int32_t entries_count);

// Note: this is a list of string pointers
extern std::vector<u_int32_t> entry_list;

extern std::vector<Language> language_list;

#endif