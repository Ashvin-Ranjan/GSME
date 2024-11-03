#ifndef GMSE_CODE_CHUNK_H
#define GMSE_CODE_CHUNK_H

#include "../chunk/chunk.h"

struct GameCode {
    u_int32_t name_pointer;
    u_int32_t length;
    u_int32_t bytecode_address;
    u_int16_t locals_count;
    u_int16_t argument_count;
    u_int8_t flags;
};

#endif