#include "Renderer.h"

#include <iostream>

Renderer::Renderer() : stepsText(font), winText(font) {
    loadTextures();
    sprite = std::make_unique<sf::Sprite>(textures[Tile::Empty]);
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    stepsText.setCharacterSize(24);
    stepsText.setFillColor(sf::Color::White);
    stepsText.setPosition({10.f, 10.f});

    winText.setString("LEVEL COMPLETED!\nPress ENTER for Next");
    winText.setCharacterSize(42);
    winText.setFillColor(sf::Color::Yellow);
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(2.f);
}

void Renderer::render(sf::RenderWindow &window, const Level &level) {
    window.clear(sf::Color(30, 30, 30));
    const auto& map = level.getMap();

    draw(window, level);

    stepsText.setString("Steps: " + std::to_string(level.getSteps()));
    window.draw(stepsText);

    if (level.checkWin()) {
        sf::FloatRect bounds = winText.getLocalBounds();
        winText.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        winText.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});
        window.draw(winText);
    }
}
void Renderer::drawObject(sf::RenderWindow &window, int x, int y, Tile type) {
    constexpr float tileSize = 64.0f;
    sprite->setTexture(textures[type]);
    sprite->setPosition({x * tileSize, y * tileSize});
    window.draw(*sprite);
}

void Renderer::draw(sf::RenderWindow &window, const Level& level) {
    const auto& map = level.getMap();
    const auto& player = level.getPlayer();
    const auto& boxes = level.getBoxes();

    for (int y = 0; y < map.getHeight(); y++) {
        for (int x = 0; x < map.getWidth(); x++) {
            drawObject(window, x, y, Tile::Empty);
            Tile type = map.getTile(x, y);
            if (type != Tile::Empty) {
                drawObject(window, x, y, type);
            }
        }
    }
    for (auto& box : boxes) {
        drawObject(window, box.getPosition().x, box.getPosition().y, Tile::Box);
    }
    drawObject(window, player.getPosition().x, player.getPosition().y, Tile::Player);
}


void Renderer::loadTextures() {
    std::map<Tile, std::string> filePaths = {
        {Tile::Wall,   "assets/wall.png"},
        {Tile::Empty,  "assets/floor.png"},
        {Tile::Box,    "assets/box.png"},
        {Tile::Player, "assets/player.png"},
        {Tile::Target, "assets/target.png"},
        {Tile::Void,   "assets/void.png"},
    };
    for (const auto& [type, path] : filePaths) {
        if (!textures[type].loadFromFile(path)) {
            std::cout << "Failed to load texture: " << path << std::endl;
        }
    }
}