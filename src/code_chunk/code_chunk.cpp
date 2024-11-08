#include "code_chunk.h"
#include "bytecode.h"
#include "../main.h"
#include "../utils/utils.h"
#include "../gen8_chunk/gen8_chunk.h"

GameCode load_code(u_int32_t offset, Chunk* code_chunk) {
    if (!compare_ident(code_chunk->ident, "CODE")) {
        throw std::invalid_argument("code chunk supplied does not have identifier `CODE`");
    }

    u_int8_t* reader = global_data.file_start + offset;

    GameCode code;
    code.name_pointer = read_safe((u_int32_t*&)reader, code_chunk);
    code.length = read_safe((u_int32_t*&)reader, code_chunk);
    // TODO: ensure that game_info is loaded before this function is called
    // if it is not then it might be reading garbage data and do something wrong
    if (game_info.format_id <= 14) {
        load_bytecode(reader - global_data.file_start, code.length);
        code.bytecode_pointer = reader - global_data.file_start;
        return code;
    }
    code.locals_count = read_safe((u_int16_t*&)reader, code_chunk);
    u_int16_t v = read_safe((u_int16_t*&)reader, code_chunk);
    code.argument_count = v & 0b1111111111111;
    code.flags = (u_int8_t)(v >> 13);
    // TODO: Finish this when I'm not tired

    return code;
}