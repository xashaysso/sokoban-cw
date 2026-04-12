#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class MenuRenderer {
    public:
        MenuRenderer();
        void render(sf::RenderWindow& window, std::vector<std::string>& options, int selectedOption);
    private:
        sf::Font font;
        void setupText(sf::Text& text, const std::string& str, float yPos);
};

