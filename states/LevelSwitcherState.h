#pragma once
#include "AppState.h"
#include "../graphics/LevelSwitcherRenderer.h"

class StateManager;

class LevelSwitcherState: public AppState {
public:
    LevelSwitcherState(StateManager &manager);

    void handleInput(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void update(float dt) override;
private:
    StateManager& manager;
    LevelSwitcherRenderer renderer;

    int totalLevels;
    int unlockedLevel = 1;
    int selectedIndex = 0;
};
