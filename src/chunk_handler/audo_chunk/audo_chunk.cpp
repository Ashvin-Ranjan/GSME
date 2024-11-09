#include "../chunk_handler.h"
#include "../../main.h"
#include "../../utils/utils.h"

std::unordered_map<u_int32_t, Audio> audio_map;

void free_audio_data() {
    for (std::pair<u_int32_t, Audio> bc : audio_map) {
        delete[] bc.second.data;
    }
}

void load_audio_data(Chunk* audio_chunk) {
    if (!compare_ident(audio_chunk->ident, "AUDO")) {
        throw std::invalid_argument("Audio chunk supplied does not have identifier `AUDO`");
    }

    u_int32_t* reader = (u_int32_t*)audio_chunk->start + 2;

    u_int32_t length = read_safe(reader, audio_chunk);

    for (int i = 0; i < length; i++) {
        u_int32_t loc = read_safe(reader, audio_chunk);
        audio_map[loc] = load_audio(loc, audio_chunk);
    }
}


Audio load_audio(u_int32_t offset, Chunk* audio_chunk) {
    u_int8_t* reader = global_data.file_start + offset;
    u_int32_t length = read_safe((u_int32_t*&)reader, audio_chunk);

    if ((reader - audio_chunk->start) + length > audio_chunk->size) {
        throw std::out_of_range("Audio supplied exceeds bounds of `AUDO` chunk");
    }

    u_int8_t* data_pointer = new u_int8_t[length];
    for (int i = 0; i < length; i++) {
        *data_pointer = *reader;
        data_pointer++;
        reader++;
    }
    Audio audio = Audio{
        data_pointer - length,
        length,
    };
    return audio;
}