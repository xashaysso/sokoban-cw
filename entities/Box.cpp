#include "Box.h"

Box::Box(sf::Vector2i startPos) {
    position = startPos;
}

void Box::setPosition(sf::Vector2i newPosition) {
    position = newPosition;
}

sf::Vector2i Box::getPosition() const {
    return position;
}

