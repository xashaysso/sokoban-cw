#include "Player.h"
#include "Box.h"
#include "../core/Level.h"

Player::Player(sf::Vector2i startPos) {
    position = startPos;
    visualPosition = { static_cast<float>(startPos.x) * 64.f, static_cast<float>(startPos.y) * 64.f };
    visualSpeed = 25.0f;
}

sf::Vector2i Player::getPosition() const {
    return position;
}

void Player::setPosition(const sf::Vector2i newPosition) {
    position = newPosition;
}

sf::Vector2f Player::getVisualPosition() const {
    return visualPosition;
}

void Player::update(const float dt) {
    const sf::Vector2f targetPos = {static_cast<float>(position.x) * 64.f, static_cast<float>(position.y) * 64.f};

    visualPosition += (targetPos - visualPosition) * visualSpeed * dt;

    if (std::abs(visualPosition.x - targetPos.x) < 1.0f && std::abs(visualPosition.y - targetPos.y) < 1.0f) {
        visualPosition = targetPos;
    }
}

void Player::syncVisualPosition() {
    visualPosition = { static_cast<float>(position.x) * 64.f, static_cast<float>(position.y) * 64.f };
}

bool Player::isMoving() const {
    const sf::Vector2f targetPos = { static_cast<float>(position.x) * 64.f, static_cast<float>(position.y) * 64.f };
    return (std::abs(visualPosition.x - targetPos.x) > 1.0f ||
            std::abs(visualPosition.y - targetPos.y) > 1.0f);
}






