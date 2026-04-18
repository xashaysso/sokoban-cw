#include "PlayState.h"

#include <fstream>
#include <iostream>

#include "MenuState.h"
#include "PauseState.h"
#include "WinState.h"
#include "../core/StateManager.h"

PlayState::PlayState(StateManager& manager, sf::RenderWindow& window, std::string path): manager(manager), level(path), tileSize(64u), renderWindow(window) {
    initWindow(window);
    auto& audio = manager.getAudio();
    winStatePushed = false;
    audio.loadSound("walk", "audio/footstep.wav");
    audio.loadSound("push", "audio/box.wav");
    audio.startMusic("audio/game.ogg",20.0f);
}

void PlayState::initWindow(sf::RenderWindow& window) const {
    unsigned int newWidth = level.getWidth() * tileSize;
    unsigned int newHeight = level.getHeight() * tileSize;

    window.setSize({newWidth, newHeight});
    const sf::View newView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(newWidth), static_cast<float>(newHeight)}));
    window.setView(newView);
    std::cout << "Window resized to: " << newWidth << ", " << newHeight << std::endl;
}


void PlayState::handleInput(sf::RenderWindow &window){
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
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

void PlayState::update(const float dt){
    if (level.checkWin() && !winStatePushed && !level.isAnimating()) {
        winStatePushed = true;

        if (!level.isLastLevel()) {
            Level::saveProgress(level.getCurrentLevelIndex() + 2);
        }
        float finalTime = levelClock.getElapsedTime().asSeconds();
        auto nextLevelCallback = [this]() {
            if (this->level.isLastLevel()) {
                this->manager.changeState(std::make_unique<MenuState>(manager, renderWindow));
            } else {
                this->level.next();
                this->winStatePushed = false;
                this->levelClock.restart();
                this->initWindow(this->renderWindow);
            }
        };

        manager.pushState(std::make_unique<WinState>(manager, level.getSteps(), finalTime, level.isLastLevel(), nextLevelCallback));
    }
    level.update(dt);
}




