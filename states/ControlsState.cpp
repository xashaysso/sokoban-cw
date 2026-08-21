#include "ControlsState.h"

#include <iostream>

#include "../core/StateManager.h"

ControlsState::ControlsState(StateManager&manager): manager(manager), helpText(font){
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    helpText.setFont(font);
    helpText.setFillColor(sf::Color::White);
    helpText.setString(
        "CONTROLS:\n\n"
        "WASD / Arrows - Move\n"
        "Z - Undo Move\n"
        "R - Restart Level\n"
        "TAB - Xray\n"
        "ESC - Pause Game\n\n"
        "Press any key to return..."
    );

    overlay.setFillColor(sf::Color(0, 0, 0, 230));
}

void ControlsState::update(float dt) {}

void ControlsState::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    auto fontSize = static_cast<unsigned int>(windowHeight * 0.05f);

    overlay.setSize({windowWidth, windowHeight});
    window.draw(overlay);

    sf::FloatRect textBounds = helpText.getLocalBounds();

    helpText.setCharacterSize(fontSize);

    helpText.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    helpText.setPosition({
        windowWidth / 2.0f,
        windowHeight / 2.0f
    });

    window.draw(helpText);
}

void ControlsState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::MouseButtonPressed>()) {
            manager.popState();
        }
    }
}


