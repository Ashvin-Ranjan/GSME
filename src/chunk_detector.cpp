#include "chunk_detector.h"

// Format information taken from: https://github.com/panzi/cook-serve-hoomans/blob/master/fileformat.md

// Size is stored in little endian format right after the identifier
u_int32_t to_size(u_int8_t* data) {
    return (u_int32_t)data[0] + (u_int32_t)data[1] << 8 + (u_int32_t)data[2] << 16 + (u_int32_t)data[3] << 24;
}

// It is important to make sure this doesn't go out of bounds of the buffer
// otherwise it will probably segfault
std::vector<Chunk> locate_chunks(u_int8_t* data, u_int32_t size) {
    if (size < 8) {
        throw std::invalid_argument("EOF Reached unexpectedly");
    }

    std::vector<Chunk> chunks;

    Chunk form = {
        { data[0], data[1], data[2], data[3] },
        to_size(data+4),
        data,
    };

    if (form.size + 8 != size) {
        throw std::invalid_argument("Malformed FORM chunk: Invalid size");
    }

    chunks.push_back(form);

    data += 8; // Move to the first actual chunk
    long offset = 8;

    while (offset < size - 8) { // It is size - 8 because 8 bytes are read from the start
        Chunk chunk = {
            { data[0], data[1], data[2], data[3] },
            to_size(data+4),
            data,
        };

        data += chunk.size; // Move to the first actual chunk
    }
}
