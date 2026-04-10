#include "PlayState.h"

#include <iostream>

PlayState::PlayState(StateManager& manager): manager(manager), level("levels/level1.txt") {}

void PlayState::handleInput(sf::RenderWindow &window){
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (level.checkWin()) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                std::cout << "Level completed" << std::endl;
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    level.next();

                    unsigned int newWidth = level.getWidth() * tileSize;
                    unsigned int newHeight = level.getHeight() * tileSize;

                    window.setSize({newWidth, newHeight});
                    sf::View newView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(newWidth), static_cast<float>(newHeight)}));
                    window.setView(newView);

                    std::cout << "Window resized to: " << newWidth << ", " << newHeight << std::endl;
                }
            }
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            level.handleInput(keyPressed->code, window);
        }
    }
}

void PlayState::draw(sf::RenderWindow &window){
    renderer.render(window, level);
}



