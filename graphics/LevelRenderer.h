#pragma once

#include <map>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "../common/Types.h"
#include "../core/Level.h"

class LevelRenderer {
    public:
        sf::Font font;
        std::map<Tile, sf::Texture> textures;
        std::unique_ptr<sf::Sprite> sprite;
        sf::Text stepsText;
        sf::Text timeText;
        LevelRenderer();
        void render(sf::RenderWindow& window, const Level& level, float elapsedTime, bool xrayMode);
    private:
        void draw(sf::RenderWindow& window, const Level& level, bool xrayMode);
        void drawObject(sf::RenderWindow& window, sf::Vector2f pixelPos, Tile type, sf::Color color);
        void loadTextures();
};
