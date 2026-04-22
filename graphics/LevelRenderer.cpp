#include "LevelRenderer.h"

#include <iostream>

LevelRenderer::LevelRenderer() : stepsText(font), timeText(font){
    loadTextures();
    sprite = std::make_unique<sf::Sprite>(textures[Tile::Empty]);
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    stepsText.setCharacterSize(24);
    stepsText.setFillColor(sf::Color::White);
    stepsText.setPosition({10.f, 10.f});

    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition({10.f, 10.f});
}

void LevelRenderer::render(sf::RenderWindow &window, const Level &level, float elapsedTime) {
    window.clear(sf::Color(30, 30, 30));
    draw(window, level);

    stepsText.setString("Steps: " + std::to_string(level.getSteps()));

    int totalSeconds = static_cast<int>(elapsedTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream timeStream;
    timeStream << "Time: "
               << std::setfill('0') << std::setw(2) << minutes << ":"
               << std::setfill('0') << std::setw(2) << seconds;

    timeText.setString(timeStream.str());

    float padding = 10.0f;
    float windowWidth = static_cast<float>(window.getSize().x);
    sf::FloatRect textBounds = timeText.getLocalBounds();

    timeText.setPosition({
        windowWidth - textBounds.size.x - padding,
        padding
    });

    sf::View gameView = window.getView();
    window.setView(window.getDefaultView());
    window.draw(stepsText);
    window.draw(timeText);
    window.setView(gameView);
}
void LevelRenderer::drawObject(sf::RenderWindow &window, sf::Vector2f pixelPos, Tile type) {
    sprite->setTexture(textures[type]);
    sprite->setPosition(pixelPos);
    window.draw(*sprite);
}

void LevelRenderer::draw(sf::RenderWindow &window, const Level& level) {
    const auto& map = level.getMap();
    const auto& player = level.getPlayer();
    const auto& boxes = level.getBoxes();

    for (int y = 0; y < map.getHeight(); y++) {
        for (int x = 0; x < map.getWidth(); x++) {
            constexpr float tileSize = 64.0f;
            drawObject(window, {x * tileSize, y * tileSize}, Tile::Empty);
            Tile type = map.getTile(x, y);
            if (type != Tile::Empty) {
                drawObject(window, {x * tileSize, y * tileSize}, type);
            }
        }
    }
    for (auto& box : boxes) {
        drawObject(window, box.getVisualPosition(), Tile::Box);
    }
    drawObject(window, player.getVisualPosition(), Tile::Player);
}


void LevelRenderer::loadTextures() {
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