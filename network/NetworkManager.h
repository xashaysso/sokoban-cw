#pragma once
#include <functional>
#include <optional>
#include <string>


struct UserStatsResponse;
struct LevelStatsResponse;
struct LevelStatsRequest;

class NetworkManager {
public:
    NetworkManager(std::string  baseUrl);
    void sendLevelStats(int levelId, const LevelStatsRequest& stats, const std::function<void(bool success)>& callback = nullptr) const;
    void getLevelStats(int levelId, const std::function<void(bool success, const std::vector<LevelStatsResponse>& stats)>& callback = nullptr) const;
    void getUserStats(const std::string& username, const std::function<void(bool success, const std::vector<UserStatsResponse>& stats)>& callback) const;
private:
    std::string m_baseUrl;
};
