#pragma once
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

    NetworkManager net{"http://127.0.0.1:8080"};

    std::vector<UserStatsResponse> leaderboard;
    std::mutex dataMutex;
    bool isLoading = true;
    bool hasError = false;
};

