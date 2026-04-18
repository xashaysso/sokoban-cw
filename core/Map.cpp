#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(const std::string& filePath) {
    loadMap(filePath);
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (getTile(x, y) == Tile::Player) {
                map[y][x] = Tile::Empty;
                startCoordinates = {x, y};
            }
        }
    }
}

Tile Map::getTile(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(map.size()) || x < 0 || x >= static_cast<int>(map[y].size())) {
        return Tile::Void;
    }
    return map[y][x];
}


int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

sf::Vector2i Map::getStartCoordinates() const {
    return startCoordinates;
}

const std::vector<std::vector<Tile>> &Map::getMap() const {
    return map;
}

void Map::loadMap(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening map file: " << filePath << std::endl;
    }
    map.clear();
    width = 0;
    height = 0;

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
        if (line.size() > width) width = line.size();
    }
    height = lines.size();
    file.close();

    for (const auto& l : lines) {
        std::vector<Tile> row;
        for (int x = 0; x < width; x++) {
            if (x < l.size()) {
                row.push_back(static_cast<Tile>(l[x]));
            } else {
                row.push_back(Tile::Void);
            }
        }
        map.push_back(row);
    }
}

void Map::setTile(int x, int y, const Tile &tile) {
    if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
        map[y][x] = tile;
    }
}




