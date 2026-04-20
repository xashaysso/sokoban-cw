#include "WinState.h"

#include <iostream>
#include <utility>

#include "MenuState.h"

WinState::WinState(StateManager &manager, const int steps, const float time, const bool isLast, std::function<void()> onConfirm): manager(manager), finalSteps(steps), finalTime(time), lastLevel(isLast), onConfirm(std::move(onConfirm)) {
    auto& audio = manager.getAudio();
    audio.loadSound("win", "audio/win.wav");
    audio.playSound("win", 60.0f);
}


void WinState::draw(sf::RenderWindow &window) {
    renderer.render(window, finalSteps, finalTime, lastLevel);
}

void WinState::update(float dt) {}

void WinState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            std::cout << "Level completed" << std::endl;

            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                auto& m = manager;
                m.popState();
                onConfirm();
                return;
            }
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                manager.changeState(std::make_unique<MenuState>(manager, window));
                return;
            }
        }
    }
}


