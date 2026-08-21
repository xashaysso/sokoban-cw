#pragma once
#include <atomic>

#include "AppState.h"
#include "../graphics/StatsRenderer.h"
#include "../network/NetworkManager.h"

class StateManager;

class StatsState: public AppState {
public:
    StatsState(StateManager& manager);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
private:
    StateManager& manager;
    StatsRenderer renderer;
    NetworkManager net;

    std::vector<UserStatsResponse> leaderboard;
    std::mutex dataMutex;
    bool isLoading = true;
    bool hasError = false;

    std::shared_ptr<std::atomic<bool>> isAlive = std::make_shared<std::atomic<bool>>(true);
};

