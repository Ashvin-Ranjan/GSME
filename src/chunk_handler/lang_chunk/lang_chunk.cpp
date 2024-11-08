#include "../chunk_handler.h"
#include "../../utils/utils.h"

std::vector<u_int32_t> entry_list;

std::vector<Language> language_list;

Language load_language(u_int32_t*& reader, Chunk* lang_chunk, u_int32_t entries_count) {
    if (!compare_ident(lang_chunk->ident, "LANG")) {
        throw std::invalid_argument("Language chunk supplied does not have identifier `LANG`");
    }

    Language lang;
    lang.name_pointer = read_safe(reader, lang_chunk);
    lang.region_pointer = read_safe(reader, lang_chunk);
    for (int i = 0; i < entries_count; i++) {
        lang.entry_pointers.push_back(read_safe(reader, lang_chunk));
    }
    return lang;
}

void load_languages(Chunk* lang_chunk) {
    if (!compare_ident(lang_chunk->ident, "LANG")) {
        throw std::invalid_argument("Language chunk supplied does not have identifier `LANG`");
    }

    // There is an initial 4 byte number which is unknown
    // Maybe it's a wide boolean saying whether the LANG chunk is empty??

    u_int32_t* reader = (u_int32_t*)lang_chunk->start + 3;
    u_int32_t entries_count = read_safe(reader, lang_chunk);
    u_int32_t lang_count = read_safe(reader, lang_chunk);
    for (int i = 0; i < entries_count; i++) {
        entry_list.push_back(read_safe(reader, lang_chunk));
    }
    for (int i = 0; i < lang_count; i++) {
        language_list.push_back(load_language(reader, lang_chunk, entries_count));
    }
}