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
                    if (selectedIndex + 1 <= unlockedLevel) {
                        int levelNum = selectedIndex + 1;
                        std::string levelPath = std::format("levels/level{:02d}.txt", levelNum);
                        manager.changeState(std::make_unique<PlayState>(manager, window, levelPath));
                    }
                    break;
                case sf::Keyboard::Key::Escape:
                    manager.popState();
                    break;
            }
        }
    }
}

void LevelSwitcherState::draw(sf::RenderWindow &window) {
    renderer.render(window, totalLevels, unlockedLevel, selectedIndex);
}

void LevelSwitcherState::update(float dt) {}


