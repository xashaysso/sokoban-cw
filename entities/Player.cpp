#include "Player.h"
#include "Box.h"
#include "../core/Level.h"

Player::Player(sf::Vector2i startPos) {
    position = startPos;
}

sf::Vector2i Player::getPosition() const {
    return position;
}

void Player::setPosition(sf::Vector2i newPosition) {
    position = newPosition;
}


