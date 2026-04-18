#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"


class WinRenderer {
    public:
        WinRenderer();
        void render(sf::RenderWindow &window, int steps, float time, bool isLastLevel);
    private:
        sf::Font font;
        sf::Text titleText;
        sf::Text statsText;
        sf::Text hintText;
        sf::RectangleShape overlay;
};
