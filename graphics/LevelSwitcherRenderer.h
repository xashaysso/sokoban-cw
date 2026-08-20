#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class LevelSwitcherRenderer {
public:
    LevelSwitcherRenderer();
    void render(sf::RenderWindow& window, int totalLevels, int unlockedLevel, int selectedIndex);
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text cardText;
    sf::Text hintText;
    sf::RectangleShape cardBox;
    sf::RectangleShape overlay;
};
