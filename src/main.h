#ifndef GMSE_MAIN_H
#define GMSE_MAIN_H

#include <stdint.h>

struct GlobalGameData {
    u_int8_t* file_start;
};

extern GlobalGameData global_data;

#endif