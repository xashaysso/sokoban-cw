#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct LevelStatsRequest {
    std::string username;
    int steps;
    int time;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    LevelStatsRequest,
    username,
    steps,
    time
)

struct LevelStatsResponse {
    int id;
    std::string username;
    int level_id;
    int steps;
    int time;
    std::string created_at;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    LevelStatsResponse,
    id,
    username,
    level_id,
    steps,
    time,
    created_at
)

struct UserStatsResponse {
    int level_id;
    int steps;
    int time;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    UserStatsResponse,
    level_id,
    steps,
    time
)