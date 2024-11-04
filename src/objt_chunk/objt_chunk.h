#ifndef GMSE_OBJT_CHUNK_H
#define GMSE_OJBT_CHUNK_H

#include "../chunk/chunk.h"

struct PhysicsVertex {
    float x; float y;
};

struct PhysicsData {
    std::vector<PhysicsVertex> verticies;
    u_int32_t shape;
    float denisty;
    float restitution;
    u_int32_t group;
    float linear_damping;
    float angular_damping;
    u_int32_t vertex_count;
    float friction;
    bool awake; // Note: stored as int32
    bool kinematic; // Note: stored as int32
    bool enabled;
    bool sensor;
};

struct GameObject {
    PhysicsData* physics;
    u_int32_t name_pointer;
    u_int32_t sprite_id;
    u_int32_t depth;
    u_int32_t parent_object_id;
    u_int32_t mask_id;
    bool managed; // TODO: Figure out how to check if this exists or not
    bool visible;
    bool solid;
    bool persistent;
};

#endif