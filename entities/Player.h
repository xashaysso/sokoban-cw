#pragma once
#include "../core/Map.h"
#include "SFML/System/Vector2.hpp"

class Player {
    public:
        Player(sf::Vector2i position);
        sf::Vector2i getPosition() const;
        void setPosition(sf::Vector2i newPosition);
    private:
        sf::Vector2i position;
};
