#pragma once
#include "AppState.h"
#include "../core/StateManager.h"
#include "../graphics/WinRenderer.h"


class WinState: public AppState {
    public:
        WinState(StateManager& manager, int steps, float time, bool isLast, std::function<void()> onConfirm);
        void handleInput(sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
    private:
        StateManager& manager;
        WinRenderer renderer;
        int finalSteps;
        float finalTime;
        bool lastLevel;
        std::function<void()> onConfirm;
};
