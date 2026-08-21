#include "MenuRenderer.h"

#include <iostream>

MenuRenderer::MenuRenderer() {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void MenuRenderer::render(sf::RenderWindow &window, std::vector<std::string>& options, int selectedOption, bool hasSave) const {
    window.clear(sf::Color(30, 30, 30));

    auto texts = createOptionTexts(options, window.getSize());

    for (size_t i = 0; i < texts.size(); i++) {
        if (i == 1 && !hasSave) {   // options[1] == continue
            texts[i].setFillColor(sf::Color(128, 128, 128));
        } else {
            texts[i].setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        }
        window.draw(texts[i]);
    }
}

std::vector<sf::Text> MenuRenderer::createOptionTexts(const std::vector<std::string> &options, sf::Vector2u windowSize) const {
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    auto fontSize = static_cast<unsigned int>(windowHeight * 0.08f);
    float spacing = fontSize * 1.3f;

    float totalBlockHeight = (options.size() - 1) * spacing;
    float startY = (windowHeight / 2.0f) - (totalBlockHeight / 2.0f);

    std::vector<sf::Text> texts;
    texts.reserve(options.size());

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text(font, options[i], fontSize);
        sf::FloatRect textBounds = text.getLocalBounds();

        text.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.0f,
            textBounds.position.y + textBounds.size.y / 2.0f
        });

        text.setPosition({
            windowWidth / 2.0f,
            startY + (i * spacing)
        });

        texts.push_back(text);
    }

    return texts;
}

int MenuRenderer::getHoveredOption(sf::Vector2f mousePos, const std::vector<std::string> &options, sf::Vector2u windowSize) const {
    auto texts = createOptionTexts(options, windowSize);

    for (size_t i = 0; i < texts.size(); i++) {
        if (texts[i].getGlobalBounds().contains(mousePos)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}