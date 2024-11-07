#include "gen8_chunk.h"
#include "../utils/utils.h"
#include "../strg_chunk/strg_chunk.h"

#include <format>

GameInfo game_info;

void set_uuid_pointer(u_int8_t uuid_pointer[8], __uint128_t value) {
    u_int8_t* p = (u_int8_t*)&value;
    for (int i = 0; i < 8; i++) {
        uuid_pointer[i] = *(p++);
    }
}

void print_game_info(bool strings_initialized = false) {
    printf(
        "Disable Debug: %i\n"
        "Format Id: %i\n"
        "Unknown: %i\n"
        "Last Object Id: %i\n"
        "Last Tile Id: %i\n"
        "Game Id: %i\n"
        "Major Version: %i\n"
        "Minor Version: %i\n"
        "Release: %i\n"
        "Build: %i\n"
        "Default Window Width: %i\n"
        "Default Window Height: %i\n"
        "Info Flags: %i\n"
        "Timestamp: %llu\n"
        "Function Classifiction: %llu\n"
        "Room Count: %i\n",
        game_info.disable_debug,
        game_info.format_id,
        game_info.unknown,
        game_info.last_object_id,
        game_info.last_tile_id,
        game_info.game_id,
        game_info.major_version,
        game_info.minor_version,
        game_info.release,
        game_info.build,
        game_info.default_window_width,
        game_info.default_window_height,
        game_info.info_flags,
        game_info.timestamp,
        game_info.function_classifications,
        game_info.room_count
    ); // TODO: Print UUID
    printf("Rooms: ");
    for (u_int32_t room : game_info.room_order) {
        printf("%i ", room);
    }
    printf("\n");
    if (game_info.format_id >= 14) {
        printf("Debug Port: %i\n", game_info.debug_port);
    }
    if (strings_initialized) {
        printf(
            "Filename: %s\n"
            "Config: %s\n"
            "Game Name: %s\n"
            "Display Name: %s\n",
            string_map[game_info.filename_pointer].c_str(),
            string_map[game_info.config_pointer].c_str(),
            string_map[game_info.game_name_pointer].c_str(),
            string_map[game_info.display_name_pointer].c_str()
        );
    } else {
        printf(
            "Filename Pointer: %x\n"
            "Config Pointer: %x\n"
            "Game Name Pointer: %x\n"
            "Display Name Pointer: %x\n",
            game_info.filename_pointer,
            game_info.config_pointer,
            game_info.game_name_pointer,
            game_info.display_name_pointer
        );
    }
}

void load_game_info(Chunk* gen8_chunk) {
    if (!compare_ident(gen8_chunk->ident, "GEN8")) {
        throw std::invalid_argument(
            std::format("General info chunk supplied does not have identifier `GEN8`, instead given %s", std::string(gen8_chunk->ident, 4))
        );
    }

    u_int8_t* reader = gen8_chunk->start + 8;

    game_info.disable_debug = read_safe((bool*&)reader, gen8_chunk);
    game_info.format_id = read_safe(reader, gen8_chunk);
    game_info.unknown = read_safe((u_int16_t*&)reader, gen8_chunk);
    game_info.filename_pointer = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.config_pointer = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.last_object_id = read_safe((u_int32_t*&)reader, gen8_chunk); // TODO: Fix bug here
    game_info.last_tile_id = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.game_id = read_safe((u_int32_t*&)reader, gen8_chunk);
    set_uuid_pointer(game_info.legacy_uuid, read_safe((__uint128_t*&)reader, gen8_chunk)); // TODO: Handle this better
    game_info.game_name_pointer = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.major_version = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.minor_version = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.release = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.build = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.default_window_width = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.default_window_height = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.info_flags = read_safe((u_int32_t*&)reader, gen8_chunk);
    reader += 20; // TODO: Handle licenses and all that
    game_info.timestamp = read_safe((u_int64_t*&)reader, gen8_chunk);
    game_info.display_name_pointer = read_safe((u_int32_t*&)reader, gen8_chunk);
    game_info.active_targets = read_safe((u_int64_t*&)reader, gen8_chunk);
    game_info.function_classifications = read_safe((u_int64_t*&)reader, gen8_chunk);
    reader += 4; // TODO: Handle Steam ID
    if (game_info.format_id >= 14) {
        game_info.debug_port = read_safe((u_int32_t*&)reader, gen8_chunk);
    }
    game_info.room_count = read_safe((u_int32_t*&)reader, gen8_chunk);
    for (int i = 0; i < game_info.room_count; i++) {
        game_info.room_order.push_back(read_safe((u_int32_t*&)reader, gen8_chunk));
    }
    // TODO: Handle GMS 2 UUID Verification & Additional Info
}