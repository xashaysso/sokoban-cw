#pragma once

#include "AppState.h"
#include "../graphics/PauseRenderer.h"

class StateManager;

class PauseState: public AppState{
public:
    PauseState(StateManager& manager);
    void handleInput(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
private:
    StateManager& manager;
    PauseRenderer renderer;
    std::vector<std::string> options;
    int selectedOption;
};
