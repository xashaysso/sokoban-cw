#pragma once
#include "AppState.h"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class StateManager;

class ControlsState: public AppState {
public:
    ControlsState(StateManager& manager);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
private:
    StateManager& manager;
    sf::Font font;
    sf::Text helpText;
    sf::RectangleShape overlay;
};

