#include "main.h"
#include "chunk/chunk.h"
#include "string_chunk/string_chunk.h"

GlobalGameData global_data;

int main() {
    // Read file data into memory
    FILE *f = fopen("data.win", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    u_int8_t *data_file = (u_int8_t*)malloc(fsize + 1);
    fread(data_file, fsize, 1, f);
    fclose(f);

    // Initialize main data
    global_data.file_start = data_file;
    
    std::vector<Chunk> chunks = locate_chunks(data_file, (u_int32_t)fsize);

    for (Chunk c : chunks) {
        printf("Name: %s | Size: %i | Location: %p\n", ident_to_string(c.ident).c_str(), c.size, c.start);
        if (compare_ident(c.ident, "STRG")) {
            load_strings(&c);
        }
    }

    // Free file data from memory when done
    free(data_file);
    data_file = NULL;

    return 0;
}