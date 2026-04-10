#pragma once
#include "SFML/System/Vector2.hpp"
#include "../core/Map.h"

class Box {
    public:
        Box(sf::Vector2i startPos);
        void setPosition(sf::Vector2i newPosition);
        sf::Vector2i getPosition() const;
    private:
        sf::Vector2i position;
};
