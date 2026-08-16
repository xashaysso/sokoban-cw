#pragma once
#include <functional>
#include <optional>
#include <string>


struct LevelStatsResponse;
struct LevelStatsRequest;

class NetworkManager {
public:
    NetworkManager(std::string  baseUrl);
    void sendLevelStats(int levelId, const LevelStatsRequest& stats, const std::function<void(bool success)>& callback = nullptr) const;
    void getLevelStats(int levelId, const std::function<void(bool success, const std::vector<LevelStatsResponse>& stats)>& callback = nullptr) const;
private:
    std::string m_baseUrl;
};
