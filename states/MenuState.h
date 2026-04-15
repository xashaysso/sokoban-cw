#pragma once

#include "AppState.h"
#include "../core/StateManager.h"
#include "../graphics/MenuRenderer.h"

class MenuState: public AppState {
public:
        MenuState(StateManager& manager, sf::RenderWindow& window);

        void handleInput(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;
private:
        StateManager& manager;
        MenuRenderer renderer;
        std::vector<std::string> options;
        int selectedOption;
};
