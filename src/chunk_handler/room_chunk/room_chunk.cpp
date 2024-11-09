#include "../chunk_handler.h"
#include "../../main.h"
#include "../../utils/utils.h"

// TODO: There is some sort of format check to be aware of

Room read_room(u_int32_t offset, Chunk* room_chunk) {
    u_int8_t* reader = global_data.file_start + offset;
    Room room;
    room.name_pointer = read_safe((u_int32_t*&)reader, room_chunk);
    room.caption_pointer = read_safe((u_int32_t*&)reader, room_chunk);
    room.width = read_safe((u_int32_t*&)reader, room_chunk);
    room.height = read_safe((u_int32_t*&)reader, room_chunk);
    room.speed = read_safe((u_int32_t*&)reader, room_chunk);
    room.persistent = read_safe((u_int32_t*&)reader, room_chunk) == 1; // This is stored as 8 bytes for some reason
    room.background_color = read_safe((u_int32_t*&)reader, room_chunk);
    room.draw_background_color = read_safe((bool*&)reader, room_chunk) == 1;
    room.creation_code_id = read_safe((u_int32_t*&)reader, room_chunk);
    room.flags = read_safe((u_int32_t*&)reader, room_chunk);
    // TODO: Load game objects
}