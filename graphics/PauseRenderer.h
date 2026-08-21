#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class PauseRenderer {
public:
    PauseRenderer();
    void render(sf::RenderWindow& window, std::vector<std::string>& options, int selectedOption) const;

    int getHoveredOption(sf::Vector2f mousePos, const std::vector<std::string> &options, sf::Vector2u windowSize) const;
private:
    sf::Font font;

    std::vector<sf::Text> createOptionTexts(const std::vector<std::string>& options, sf::Vector2u windowSize) const;
};
