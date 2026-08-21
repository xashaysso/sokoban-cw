#include "LevelSwitcherState.h"

#include "PlayState.h"
#include "../core/Level.h"
#include "../core/StateManager.h"

LevelSwitcherState::LevelSwitcherState(StateManager &manager): manager(manager) {
    unlockedLevel = Level::loadProgress();
    if (unlockedLevel < 1) unlockedLevel = 1;

    totalLevels = Level::getLevelCount();

    selectedIndex = std::min(unlockedLevel - 1, totalLevels - 1);
}

void LevelSwitcherState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseMoved->position);
            int hoveredIdx = getCardIndexAt(mousePos);
            if (hoveredIdx != -1) {
                selectedIndex = hoveredIdx;
            }
        }

        if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseBtn->position);
                int clickedIdx = getCardIndexAt(mousePos);
                if (clickedIdx != -1) {
                    selectedIndex = clickedIdx;
                    launchSelectedLevel(window);
                    return;
                }
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            const auto key = keyPressed->code;
            const int cols = 5;

            switch (key) {
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    if (selectedIndex + 1 < totalLevels) selectedIndex++;
                    break;
                case sf::Keyboard::Key::Left:
                case sf::Keyboard::Key::A:
                    if (selectedIndex - 1 >= 0) selectedIndex--;
                    break;
                case sf::Keyboard::Key::Down:
                case sf::Keyboard::Key::S:
                    if (selectedIndex + cols < totalLevels) selectedIndex+=cols;
                    break;
                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    if (selectedIndex - cols >= 0) selectedIndex-=cols;
                    break;
                case sf::Keyboard::Key::Enter:
                    launchSelectedLevel(window);
                    break;
                case sf::Keyboard::Key::Escape:
                    manager.popState();
                    break;
            }
        }
    }
}

void LevelSwitcherState::launchSelectedLevel(sf::RenderWindow &window) {
    if (selectedIndex + 1 <= unlockedLevel) {
        int levelNum = selectedIndex + 1;
        std::string levelPath = std::format("levels/level{:02d}.txt", levelNum);
        manager.changeState(std::make_unique<PlayState>(manager, window, levelPath));
    }
}

int LevelSwitcherState::getCardIndexAt(sf::Vector2f mousePos) const {
    const int cols = 5;
    const float startX = 232.f;
    const float startY = 270.f;
    const float gapX = 140.f;
    const float gapY = 150.f;
    const float cardHalfSize = 55.f;

    for (int i = 0; i < totalLevels; ++i) {
        int col = i % cols;
        int row = i / cols;

        float posX = startX + col * gapX;
        float posY = startY + row * gapY;

        sf::FloatRect bounds({posX - cardHalfSize, posY - cardHalfSize}, {110.f, 110.f});
        if (bounds.contains(mousePos)) {
            return i;
        }
    }
    return -1;
}

void LevelSwitcherState::draw(sf::RenderWindow &window) {
    renderer.render(window, totalLevels, unlockedLevel, selectedIndex);
}

void LevelSwitcherState::update(float dt) {}


