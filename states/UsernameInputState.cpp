#include "UsernameInputState.h"

#include <fstream>

#include "MenuState.h"
#include "../core/StateManager.h"

UsernameInputState::UsernameInputState(StateManager &manager, sf::RenderWindow &window): manager(manager) {}

void UsernameInputState::saveUsername(std::string username) {
    nlohmann::json saveData;

    if (std::ifstream inFile("save.json"); inFile.is_open()) {
        try {
            inFile >> saveData;
        } catch (...) {}
    }

    saveData["username"] = username;
    if (std::ofstream outFile("save.json"); outFile.is_open()) {
        outFile << saveData.dump(4);
    }
}

std::string UsernameInputState::loadUsername() {
    if (std::ifstream inFile("save.json"); inFile.is_open()) {
        try {
            nlohmann::json saveData;
            inFile >> saveData;
            if (saveData.contains("username") && saveData["username"].is_string()) {
                return saveData["username"].get<std::string>();
            }
        } catch (...) {}
    }
    return "";
}

void UsernameInputState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
            char32_t unicode = textEntered->unicode;

            if (unicode == 8) {
                if (!inputString.empty()) {
                    inputString.pop_back();
                }
            } else if (unicode > 32 && unicode < 127 && inputString.size() < maxUsernameLength) {
                inputString += static_cast<char>(unicode);
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter && !inputString.empty()) {
                saveUsername(inputString);
                manager.changeState(std::make_unique<MenuState>(manager, window));
            }
        }
    }
}

void UsernameInputState::update(float dt) {
    cursorTimer += dt;
    if (cursorTimer > 0.5f) {
        showCursor = !showCursor;
        cursorTimer = 0.0f;
    }
}

void UsernameInputState::draw(sf::RenderWindow &window) {
    renderer.render(window, inputString, showCursor);
}
