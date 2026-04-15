#include "MenuRenderer.h"

#include <iostream>

MenuRenderer::MenuRenderer() {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void MenuRenderer::render(sf::RenderWindow &window, std::vector<std::string>& options, int selectedOption) const {
    window.clear(sf::Color(30, 30, 30));
    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text(font, options[i], 50);
        float x = window.getSize().x / 2.0f - text.getGlobalBounds().size.x / 2.0f;
        float y = 200.0f + i * 100.0f;
        text.setPosition({x, y});
        text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        window.draw(text);
    }
}
