#include "../chunk_handler.h"

// Format information taken from: https://github.com/panzi/cook-serve-hoomans/blob/master/fileformat.md

// It is important to make sure this doesn't go out of bounds of the buffer
// otherwise it will probably segfault
std::vector<Chunk> locate_chunks(u_int8_t* data, u_int32_t size) {
    if (size < 8) {
        throw std::invalid_argument("EOF Reached unexpectedly");
    }

    std::vector<Chunk> chunks;

    Chunk form = {
        { (char)data[0], (char)data[1], (char)data[2], (char)data[3] },
        *((u_int32_t*)data + 1),
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
            { (char)data[0], (char)data[1], (char)data[2], (char)data[3] },
            *((u_int32_t*)data + 1),
            data,
        };

        chunks.push_back(chunk);

        data += chunk.size + 8;
        offset += chunk.size + 8;
    }

    return chunks;
}

std::string ident_to_string(char ident[4]) {
    return std::string(ident, 4);
}

bool compare_ident(char ident[4], const char* string) {
    for (int i = 0; i < 4; i++) {
        if (ident[i] != string[i]) {
            return false;
        }
    }
    return true;
}