#pragma once
#include <atomic>

#include "AppState.h"
#include "../core/StateManager.h"
#include "../entities/Stats.h"
#include "../graphics/WinRenderer.h"
#include "../network/NetworkManager.h"


class WinState: public AppState {
    public:
        WinState(StateManager& manager, int levelId, int steps, float time, bool isLast, std::function<void()> onConfirm);
        ~WinState();
        void handleInput(sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
    private:
        StateManager& manager;
        WinRenderer renderer;
        NetworkManager net;

        int levelId;
        int finalSteps;
        float finalTime;
        bool lastLevel;
        std::function<void()> onConfirm;

        std::vector<LevelStatsResponse> leaderboard;
        std::mutex dataMutex;
        bool isLoading = true;
        bool hasError = false;

        std::shared_ptr<std::atomic<bool>> isAlive = std::make_shared<std::atomic<bool>>(true);
};
