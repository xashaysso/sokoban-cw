#include "PauseState.h"

#include "MenuState.h"
#include "PlayState.h"
#include "../core/StateManager.h"

PauseState::PauseState(StateManager &manager): manager(manager), selectedOption(0){
    options = {"RESUME", "EXIT TO MENU"};
}


void PauseState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::W) {
                if (selectedOption == 0) {
                    selectedOption = options.size() - 1;
                } else {
                    selectedOption--;
                }
            }
            if (keyPressed->code == sf::Keyboard::Key::S) {
                if (selectedOption == options.size() - 1) {
                    selectedOption = 0;
                } else {
                    selectedOption++;
                }
            }
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                if (selectedOption == 0) {
                    manager.popState();
                } else {
                    manager.resetToState(std::make_unique<MenuState>(manager, window));
                    return;
                }
            }
        }
    }
}

void PauseState::draw(sf::RenderWindow &window) {
    renderer.render(window, options, selectedOption);
}

