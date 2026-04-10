#pragma once
#include <string>
#include <vector>

#include "../common/Types.h"
#include "SFML/System/Vector2.hpp"

class Map {
    public:
        Map(const std::string& filePath);
        int getWidth() const;
        int getHeight() const;
        sf::Vector2i getStartCoordinates() const;
        const std::vector<std::vector<Tile>>& getMap() const;
        Tile getTile(int x, int y) const;
        void setTile(int x, int y, const Tile& tile);
        void loadMap(const std::string& filePath);
    private:
        sf::Vector2i startCoordinates;
        std::vector<std::vector<Tile>> map;
        int width;
        int height;
};
