#ifndef GMSE_ROOM_CHUNK_H
#define GMSE_ROOM_CHUNK_H

#include "../chunk_handler.h"

struct Background {
    u_int32_t background_id;
    u_int32_t x; u_int32_t y;
    u_int32_t speed_x; u_int32_t speed_y;
    u_int32_t tile_x; u_int32_t tile_y;
    bool enabled;
    bool foreground;
    bool stretch;
};

struct View {
    u_int32_t view_x; u_int32_t view_y;
    u_int32_t view_width; u_int32_t view_height;
    u_int32_t port_x; u_int32_t port_y;
    u_int32_t border_x; u_int32_t border_y;
    u_int32_t speed_x; u_int32_t speed_y;
    u_int32_t follow_id;
    bool enabled;
};
struct Room {
    std::vector<GameObject> game_objects;
    Background* background;
    View* view;
    u_int32_t name_pointer;
    u_int32_t caption_pointer;
    u_int32_t width; u_int32_t height;
    u_int32_t speed;
    u_int32_t background_color;
    u_int32_t creation_code_id;
    u_int32_t flags; // TODO: Make enum
    bool persistent;
    bool draw_background_color;
};

void load_rooms(Chunk* room_chunk);

Room read_room(u_int32_t offset, Chunk* room_chunk);

#endif