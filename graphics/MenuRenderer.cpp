#include "MenuRenderer.h"

#include <iostream>

MenuRenderer::MenuRenderer() {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void MenuRenderer::render(sf::RenderWindow &window, std::vector<std::string>& options, int selectedOption, bool hasSave) const {
    window.clear(sf::Color(30, 30, 30));

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    auto fontSize = static_cast<unsigned int>(windowHeight * 0.12f);
    float spacing = fontSize * 1.5f;

    float totalBlockHeight = (options.size() - 1) * spacing;
    float startY = (windowHeight / 2.0f) - (totalBlockHeight / 2.0f);

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text(font, options[i], 50);
        sf::FloatRect textBounds = text.getLocalBounds();

        text.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.0f,
            textBounds.position.y + textBounds.size.y / 2.0f
        });

        text.setPosition({
            windowWidth / 2.0f,
            startY + (i * spacing)
        });
        if (i == 1 && !hasSave) {   // options[1] == continue
            text.setFillColor(sf::Color(128, 128, 128));
        } else {
            text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        }
        window.draw(text);
    }
}
