#include "PlayState.h"

#include <iostream>

#include "PauseState.h"
#include "../core/StateManager.h"

PlayState::PlayState(StateManager& manager, sf::RenderWindow& window): manager(manager), level("levels/level1.txt"), tileSize(64u) {
    initWindow(window);
    auto& audio = manager.getAudio();
    audio.loadSound("walk", "audio/footstep.wav");
    audio.loadSound("push", "audio/box.wav");
    audio.startMusic("audio/game.ogg",20.0f);
}

void PlayState::initWindow(sf::RenderWindow& window) const {
    unsigned int newWidth = level.getWidth() * tileSize;
    unsigned int newHeight = level.getHeight() * tileSize;

    window.setSize({newWidth, newHeight});
    sf::View newView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(newWidth), static_cast<float>(newHeight)}));
    window.setView(newView);
    std::cout << "Window resized to: " << newWidth << ", " << newHeight << std::endl;
}


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
                    initWindow(window);
                }
            }
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                manager.pushState(std::make_unique<PauseState>(manager));
                return;
            }
            MoveResult result = level.handleInput(keyPressed->code, window);
            auto& audio = manager.getAudio();
            switch (result) {
                case MoveResult::Walk:
                    audio.playSound("walk", 2.f);
                    break;
                case MoveResult::Push:
                    audio.playSound("push", 1.f);
                    break;
                default:
                    break;
            }
        }
    }
}

void PlayState::draw(sf::RenderWindow &window){
    renderer.render(window, level);
}



