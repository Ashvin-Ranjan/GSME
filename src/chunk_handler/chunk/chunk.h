#ifndef GMSE_CHUNK_DETECTOR_H
#define GMSE_CHUNK_DETECTOR_H

#include <stdint.h>
#include <vector>

struct Chunk {
    char ident[4];
    u_int32_t size;
    u_int8_t* start;
};

std::vector<Chunk> locate_chunks(u_int8_t* data, u_int32_t size);

std::string ident_to_string(char ident[4]);

bool compare_ident(char ident[4], const char* compare);

#endif