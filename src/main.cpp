#include "chunk_detector.h"

int main() {

    FILE *f = fopen("data.win", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    u_int8_t *data_file = (u_int8_t*)malloc(fsize + 1);
    fread(data_file, fsize, 1, f);
    fclose(f);
    

    free(data_file);
    data_file = NULL;
    
    return 0;
}