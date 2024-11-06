#ifndef GMSE_GEN8_CHUNK_H
#define GMSE_GEN8_CHUNK_H

#include "../chunk/chunk.h"

struct GameInfo {
    std::vector<u_int32_t> room_order;
    u_int8_t legacy_uuid[16];
    u_int8_t game_uuid[16];
    u_int64_t active_targets;
    u_int64_t function_classifications;
    u_int64_t timestamp;
    u_int32_t filename_pointer;
    u_int32_t config_pointer;
    u_int32_t last_object_id;
    u_int32_t last_tile_id;
    u_int32_t game_id;
    u_int32_t game_name_pointer;
    u_int32_t major_version;
    u_int32_t minor_version;
    u_int32_t release;
    u_int32_t build;
    u_int32_t default_window_width;
    u_int32_t default_window_height;
    u_int32_t info_flags;
    u_int32_t display_name_pointer;
    u_int32_t room_count;
    u_int32_t debug_port;
    u_int16_t unknown; // TODO: Figure out what this does
    float fps;
    bool allow_statistics;
    bool disable_debug;
    u_int8_t format_id;
};

extern GameInfo game_info;

void print_game_info(bool strings_initialized);

void load_game_info(Chunk* gen8_chunk);

#endif