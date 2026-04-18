#pragma once
#include "../core/Map.h"
#include "SFML/System/Vector2.hpp"

class Player {
    public:
        Player(sf::Vector2i position);
        sf::Vector2i getPosition() const;
        void setPosition(sf::Vector2i newPosition);

        void update(float dt);
        sf::Vector2f getVisualPosition() const;
        void syncVisualPosition();
    private:
        sf::Vector2i position;

        sf::Vector2f visualPosition;
        float visualSpeed;
};
