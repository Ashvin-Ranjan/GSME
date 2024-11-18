#ifndef GMSE_BYTECODE_H
#define GMSE_BYTECODE_H

// Details taken from https://web.archive.org/web/20191126144953if_/https://github.com/donkeybonks/acolyte/wiki/Bytecode

#include <stdint.h>
#include <string>
#include <unordered_map>

struct ByteCode {
    u_int8_t* data;
    u_int32_t length;
};

extern std::unordered_map<u_int32_t, ByteCode> bytecode_map;

void free_bytecode_data();

void load_bytecode(u_int32_t offset, u_int32_t length);

#endif