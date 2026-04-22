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
    audio.startMusic("audio/game.ogg",30.0f);
}

void PlayState::initWindow(sf::RenderWindow& window) const {
    window.setSize({1024u, 768u});

    float levelWidth = static_cast<float>(level.getWidth() * tileSize);
    float levelHeight = static_cast<float>(level.getHeight() * tileSize);

    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (desktop.size.x - 1024) / 2,
        (desktop.size.y - 768) / 2
    ));
    sf::View newView(sf::FloatRect({0.f, 0.f}, {1024.f, 768.f}));
    newView.setCenter({levelWidth / 2.0f, levelHeight / 2.0f});
    window.setView(newView);
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
    float currentTime = levelClock.getElapsedTime().asSeconds();
    renderer.render(window, level, currentTime);
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




