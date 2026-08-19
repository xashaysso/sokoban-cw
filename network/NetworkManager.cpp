#include "NetworkManager.h"

#include <future>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

#include "../entities/Stats.h"
#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include "cpr/response.h"

NetworkManager::NetworkManager(std::string  baseUrl): m_baseUrl(std::move(baseUrl)) {};

void NetworkManager::sendLevelStats(const int levelId, const LevelStatsRequest& stats, const std::function<void(bool success)>& callback) const {
        nlohmann::json jsonBody = {
            {"username", stats.username},
            {"steps", stats.steps},
            {"time", stats.time},
        };

        std::string url = m_baseUrl + "/levels/" + std::to_string(levelId);

        cpr::PostCallback([callback, url](const cpr::Response& response) {
            const bool success = (response.status_code == 200 || response.status_code == 201);
            if (!success) {
                std::cerr << "POST " << url << " failed. Code: " << response.status_code
                << ", Error: " << response.error.message << std::endl;
            }
            if (callback) {
                callback(success);
            }
        },
        cpr::Url{url},
        cpr::Body{jsonBody.dump()},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{3000});
}

void NetworkManager::getLevelStats(const int levelId, const std::function<void(bool success, const std::vector<LevelStatsResponse>& stats)>& callback) const {
    std::string url = m_baseUrl + "/levels/" + std::to_string(levelId);

    cpr::GetCallback([callback, url](const cpr::Response& response) {
        bool success = (response.status_code == 200);
        std::vector<LevelStatsResponse> result;

        if (success) {
            try {
                const auto json = nlohmann::json::parse(response.text);
                result = json.get<std::vector<LevelStatsResponse>>();
            } catch (const std::exception& e){
                std::cerr << "JSON parse err: " << e.what() << std::endl;
                success = false;
            }
        } else {
            std::cerr << "GET " << url << " failed. Code: " << response.status_code
                << ", Error: " << response.error.message << std::endl;
        }
        if (callback) {
            callback(success, result);
        }
    },
    cpr::Url{url},
    cpr::Timeout{3000});
}

void NetworkManager::getUserStats(const std::string& username, const std::function<void(bool success, const std::vector<UserStatsResponse>& stats)>& callback) const {
    std::string url = m_baseUrl + "/players/" + username + "/records";

    cpr::GetCallback([callback, url](const cpr::Response& response) {
        bool success = (response.status_code == 200);
        std::vector<UserStatsResponse> result;

        if (success) {
            try {
                const auto json = nlohmann::json::parse(response.text);
                result = json.get<std::vector<UserStatsResponse>>();
            } catch (const std::exception& e){
                std::cerr << "JSON parse err: " << e.what() << std::endl;
                success = false;
            }
        } else {
            std::cerr << "GET " << url << " failed. Code: " << response.status_code
                << ", Error: " << response.error.message << std::endl;
        }
        if (callback) {
            callback(success, result);
        }
    },
    cpr::Url{url},
    cpr::Timeout{3000});
}
