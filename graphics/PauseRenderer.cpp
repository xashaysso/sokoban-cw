#include "PauseRenderer.h"

#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"

PauseRenderer::PauseRenderer() {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void PauseRenderer::render(sf::RenderWindow &window, std::vector<std::string>& options, int selectedOption) const {
    sf::View gameView = window.getView();
    window.setView(window.getDefaultView());

    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setPosition(sf::Vector2f(0, 0));
    window.draw(overlay);

    auto texts = createOptionTexts(options, window.getSize());

    for (size_t i = 0; i < texts.size(); i++) {
        texts[i].setFillColor(static_cast<int>(i) == selectedOption ? sf::Color::Red : sf::Color::White);
        window.draw(texts[i]);
    }
    window.setView(gameView);
}

int PauseRenderer::getHoveredOption(sf::Vector2f mousePos, const std::vector<std::string> &options, sf::Vector2u windowSize) const {
    auto texts = createOptionTexts(options, windowSize);

    for (size_t i = 0; i < texts.size(); i++) {
        if (texts[i].getGlobalBounds().contains(mousePos)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

std::vector<sf::Text> PauseRenderer::createOptionTexts(const std::vector<std::string> &options, sf::Vector2u windowSize) const {
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    unsigned int fontSize = static_cast<unsigned int>(windowHeight * 0.07f);
    float spacing = fontSize * 1.75f;
    float totalBlockHeight = (options.size() - 1) * spacing;
    float startY = (windowHeight / 2.0f) - (totalBlockHeight / 2.0f);

    std::vector<sf::Text> texts;
    texts.reserve(options.size());

    for (size_t i = 0; i < options.size(); ++i) {
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

