#include "Box.h"

Box::Box(const sf::Vector2i startPos) {
    position = startPos;
    visualPosition = { static_cast<float>(startPos.x) * 64.f, static_cast<float>(startPos.y) * 64.f };
    visualSpeed = 25.0f;
}

void Box::setPosition(const sf::Vector2i newPosition) {
    position = newPosition;
}

sf::Vector2i Box::getPosition() const {
    return position;
}

sf::Vector2f Box::getVisualPosition() const {
    return visualPosition;
}

void Box::update(const float dt) {
    const sf::Vector2f targetPos = {static_cast<float>(position.x) * 64.f, static_cast<float>(position.y) * 64.f};

    visualPosition += (targetPos - visualPosition) * visualSpeed * dt;
    if (std::abs(visualPosition.x - targetPos.x) < 0.1f && std::abs(visualPosition.y - targetPos.y) < 0.1f) {
        visualPosition = targetPos;
    }
}

void Box::syncVisualPosition() {
    visualPosition = { static_cast<float>(position.x) * 64.f, static_cast<float>(position.y) * 64.f };
}

