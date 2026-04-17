#pragma once

#include <vector>
#include <filesystem>
#include <stack>
#include <iostream>
#include <algorithm>

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "Map.h"
#include "../entities/Player.h"
#include "../entities/Box.h"
#include "../common/Types.h"

class Level {
    public:
        explicit Level(const std::string& filePath);
        int getWidth() const;
        int getHeight() const;
        Map getMap() const;
        Player getPlayer() const;
        std::vector<Box> getBoxes() const;
        Box* getBoxAt(int x, int y);
        MoveResult movePlayer(Direction dir);
        MoveResult handleInput(sf::Keyboard::Key key, sf::RenderWindow& window);
        void restart();
        int getSteps() const;
        bool checkWin() const;
        void next();
        void undo();

        static void saveProgress(int currentLevelIndex);
    private:
        Map map;
        Player player;
        std::vector<Box> boxes;
        std::vector<sf::Vector2i> targets;
        int steps;
        int currentLevel;
        std::vector<std::string> levelPaths;
        struct currState {
            std::vector<Box> boxes;
            Player player;
        };
        std::stack<currState> moves;

        bool moveBox(int dx, int dy, Box* box);
        void loadLevelData(const std::string& path);
        void initLevelList();
};
