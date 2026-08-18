#pragma once
#include "AppState.h"
#include "../core/StateManager.h"
#include "../entities/Stats.h"
#include "../graphics/WinRenderer.h"
#include "../network/NetworkManager.h"


class WinState: public AppState {
    public:
        WinState(StateManager& manager, int levelId, int steps, float time, bool isLast, std::function<void()> onConfirm);
        void handleInput(sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
    private:
        StateManager& manager;
        WinRenderer renderer;
        NetworkManager net{"http://127.0.0.1:8080"};

        int levelId;
        int finalSteps;
        float finalTime;
        bool lastLevel;
        std::function<void()> onConfirm;

        std::vector<LevelStatsResponse> leaderboard;
        std::mutex dataMutex;
        bool isLoading = true;
        bool hasError = false;
};
