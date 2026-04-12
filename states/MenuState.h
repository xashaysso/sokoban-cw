#pragma once

#include "AppState.h"
#include "../core/StateManager.h"
#include "../graphics/MenuRenderer.h"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class MenuState: public AppState {
public:
        MenuState(StateManager& manager);

        void handleInput(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;
private:
        StateManager& manager;
        MenuRenderer renderer;
        std::vector<std::string> options;
        int selectedOption;
};
