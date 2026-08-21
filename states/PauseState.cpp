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

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseMoved->position, window.getDefaultView());
            int hoveredIdx = renderer.getHoveredOption(mousePos, options, window.getSize());
            if (hoveredIdx != -1) {
                selectedOption = hoveredIdx;
            }
        }

        if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseBtn->position, window.getDefaultView());
                int clickedIdx = renderer.getHoveredOption(mousePos, options, window.getSize());
                if (clickedIdx != -1) {
                    selectedOption = clickedIdx;
                    executeOption(window);
                    return;
                }
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Up:
                    if (selectedOption == 0) {
                        selectedOption = options.size() - 1;
                    } else {
                        selectedOption--;
                    }
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    if (selectedOption == options.size() - 1) {
                        selectedOption = 0;
                    } else {
                        selectedOption++;
                    }
                    break;
                case sf::Keyboard::Key::Enter:
                    executeOption(window);
                    return;
                case sf::Keyboard::Key::Escape:
                    manager.popState();
                    return;
            }
        }
    }
}

void PauseState::draw(sf::RenderWindow &window) {
    renderer.render(window, options, selectedOption);
}

void PauseState::update(float dt) {}

void PauseState::executeOption(sf::RenderWindow &window) const {
    if (selectedOption == 0) {
        manager.popState();
    } else {
        manager.resetToState(std::make_unique<MenuState>(manager, window));
    }
}
