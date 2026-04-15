#include "PauseRenderer.h"

#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"

PauseRenderer::PauseRenderer() {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void PauseRenderer::render(sf::RenderWindow &window, std::vector<std::string>& options, int selectedOption) const {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setPosition(sf::Vector2f(0, 0));

    window.draw(overlay);

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text(font, options[i], 50);
        sf::FloatRect textBounds = text.getLocalBounds();

        text.setOrigin({textBounds.size.x / 2.0f, textBounds.size.y / 2.0f});
        text.setPosition({window.getSize().x / 2.0f, 200.0f + i * 100.0f});

        text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        window.draw(text);
    }
}
