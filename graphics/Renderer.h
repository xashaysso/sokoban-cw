#pragma once

#include <map>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "../common/Types.h"
#include "../core/Level.h"

class Renderer {
    public:
        sf::Font font;
        std::map<Tile, sf::Texture> textures;
        std::unique_ptr<sf::Sprite> sprite;
        sf::Text stepsText;
        sf::Text winText;
        Renderer();
        void render(sf::RenderWindow& window, const Level& level);
    private:
        void draw(sf::RenderWindow& window, const Level& level);
        void drawObject(sf::RenderWindow& window, int x, int y, Tile type);
        void loadTextures();
};
