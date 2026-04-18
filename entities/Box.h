#pragma once
#include "SFML/System/Vector2.hpp"
#include "../core/Map.h"

class Box {
    public:
        Box(sf::Vector2i startPos);
        void setPosition(sf::Vector2i newPosition);
        sf::Vector2i getPosition() const;

        void update(float dt);
        sf::Vector2f getVisualPosition() const;
        void syncVisualPosition();
        bool isMoving() const;
    private:
        sf::Vector2i position;

        sf::Vector2f visualPosition;
        float visualSpeed;
};
