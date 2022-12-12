#pragma once

// Default constructor for Agent struct

struct Player
{
    uint32_t agent_id;
    // Coordinates are in a left-handed system.
    // x = east (lower values) to west (higher values).
    // y = low altitude (lower value) to high altitude (higher values).
    // z = south(lower values) to north (higher values).
    float x, y, z;

    uint32_t ground;
    uint32_t h0060;

    float health; // 0 to 1
    float energy; // 0 to 1

    // instance timer in rendered framed.
    uint32_t fps_timer;
};

class ClientData
{
public:
    Player player;
};
