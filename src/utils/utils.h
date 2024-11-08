#ifndef GMSE_UTILS_H
#define GMSE_UTILS_H

#include "../chunk_handler/chunk_handler.h"
#include "../main.h"

#include <format>

// This has to be defined here
template <typename T> 
T read_safe(T*& location, Chunk* chunk_data) {
    if ((u_int8_t*)location - chunk_data->start > chunk_data->size) {
            printf("Pointer points to 0x%lx, which is out of bounds of `%s` (Type Size: %lu)\n",
                (u_int8_t*)location - global_data.file_start,
                std::string(chunk_data->ident, 4).c_str(),
                sizeof(T)
            );
        throw std::out_of_range("");
    }
    return *(location++);
}

#endif