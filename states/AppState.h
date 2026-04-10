#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class AppState {
public:
        virtual ~AppState() = default;
        virtual void handleInput(sf::RenderWindow& window) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
};

