#include "../chunk_handler.h"
#include "../../main.h"

std::unordered_map<u_int32_t, ByteCode> bytecode_map;

void free_bytecode_data() {
    for (std::pair<u_int32_t, ByteCode> bc : bytecode_map) {
        delete[] bc.second.data;
    }
}

void load_bytecode(u_int32_t offset, u_int32_t length) {
    u_int8_t* reader = global_data.file_start + offset;
    u_int8_t* data_pointer = new u_int8_t[length];
    for (int i = 0; i < length; i++) {
        *data_pointer = *reader;
        data_pointer++;
        reader++;
    }
    ByteCode bc = ByteCode{
        data_pointer,
        length,
    };
    bytecode_map[offset] = bc;
}