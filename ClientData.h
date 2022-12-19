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

    uint32_t instance_id;
    uint32_t party_id;
};

struct InstanceInfo
{
    // instance timer in rendered framed since loaded.
    uint32_t fps_timer;

    // Pair of instance_id and party_id uniquely identifies a party.
    uint32_t instance_id;
};

struct Party
{
    uint32_t party_id;
};

class ClientData
{
public:
    Player player;
    InstanceInfo instance_info;
    Party party;
};
