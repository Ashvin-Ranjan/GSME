#include "main.h"

#include "chunk_handler/chunk_handler.h"

GlobalGameData global_data;

int main(int argc, const char * argv[]) {
    const char* file;
    if (argc == 1) {
        file = "data.win";
    } else {
        file = argv[1];
    }
    // Read file data into memory
    FILE *f = fopen(file, "rb");
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
        if (compare_ident(c.ident, "GEN8")) {
            load_game_info(&c);
        }
        if (compare_ident(c.ident, "GLOB")) {
            load_global_entries(&c);
        }
        if (compare_ident(c.ident, "LANG")) {
            load_languages(&c);
        }
        if (compare_ident(c.ident, "AUDO")) {
            load_audio_data(&c);
        }
        if (compare_ident(c.ident, "SCPT")) {
            load_script_data(&c);
        }
    }
    print_game_info(true);
    for (u_int32_t i : global_code_entry) {
        printf("%u ", i);
    }
    printf("\n");

    // Free file data from memory when done
    free(data_file);
    data_file = NULL;

    // Make sure this is called to avoid issues
    // this frees up allocated memory
    free_bytecode_data();
    free_audio_data();

    return 0;
}