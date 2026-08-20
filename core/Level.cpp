#include "Level.h"

#include <fstream>

#include "nlohmann/adl_serializer.hpp"

namespace fs = std::filesystem;

Level::Level(const std::string &filePath) : map(filePath), player(map.getStartCoordinates()) {
    initLevelList();

    fs::path targetPath(filePath);

    const auto it = std::ranges::find_if(levelPaths, [&](const std::string& p) {
        return fs::path(p) == targetPath;
    });

    if (it != levelPaths.end()) {
        currentLevel = static_cast<int>(std::distance(levelPaths.begin(), it));
    } else {
        currentLevel = 0;
    }

    loadLevelData(levelPaths[currentLevel]);
}

void Level::loadLevelData(const std::string& path) {
    boxes.clear();
    targets.clear();
    steps = 0;
    moves = {};

    map.loadMap(path);
    player.setPosition(map.getStartCoordinates());

    for (int y = 0; y < map.getHeight(); y++) {
        for (int x = 0; x < map.getWidth(); x++) {
            if (map.getTile(x, y) == Tile::Box) {
                boxes.emplace_back(sf::Vector2i(x, y));
                map.setTile(x, y, Tile::Empty);
            } else if (map.getTile(x, y) == Tile::Player) {
                player.setPosition({x, y});
                player.syncVisualPosition();
                map.setTile(x, y, Tile::Empty);
            } else if (map.getTile(x, y) == Tile::Target) {
                targets.emplace_back(x, y);
            } else if (map.getTile(x, y) == Tile::BoxOnTarget) {
                boxes.emplace_back(sf::Vector2i(x, y));
                targets.emplace_back(x, y);
                map.setTile(x, y, Tile::Target);
            }
        }
    }
    changeBoxStates();
    std::cout << "Level successfully initialized/reset" << std::endl;
}


Box *Level::getBoxAt(int x, int y) {
    for (auto& box : boxes) {
        if (box.getPosition().x == x && box.getPosition().y == y) {
            return &box;
        }
    }
    return nullptr;
}

MoveResult Level::movePlayer(Direction dir) {
    const currState currState = {boxes, player};
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up: dy = -1; break;
        case Direction::Down: dy = 1; break;
        case Direction::Left: dx = -1; break;
        case Direction::Right: dx = 1; break;
    }
    int nextX = player.getPosition().x + dx;
    int nextY = player.getPosition().y + dy;

    MoveResult moveResult = MoveResult::None;

    if (Box* box = getBoxAt(nextX, nextY)) {
        if (moveBox(dx, dy, box)) {
            player.setPosition({nextX, nextY});
            moveResult = MoveResult::Push;
        }
    } else if (map.getTile(nextX, nextY) != Tile::Wall) {
        player.setPosition({nextX, nextY});
        moveResult = MoveResult::Walk;
    }
    if (moveResult != MoveResult::None) {
        moves.push(currState);
        steps++;
    }
    if (moveResult == MoveResult::Push) {
        changeBoxStates();
    }
    return moveResult;
}

bool Level::moveBox(int dx, int dy, Box* box) {
    int newX = box->getPosition().x + dx;
    int newY = box->getPosition().y + dy;
    if (getBoxAt(newX, newY) != nullptr) {
        return false;
    }
    if (map.getTile(newX, newY) == Tile::Empty || map.getTile(newX, newY) == Tile::Target) {
        box->setPosition({newX, newY});
        return true;
    }
    return false;
}

int Level::getWidth() const {
    return map.getWidth();
}

int Level::getHeight() const {
    return map.getHeight();
}

MoveResult Level::handleInput(const sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::W:
        case sf::Keyboard::Key::Up:
            return movePlayer(Direction::Up);
        case sf::Keyboard::Key::S:
        case sf::Keyboard::Key::Down:
            return movePlayer(Direction::Down);
        case sf::Keyboard::Key::A:
        case sf::Keyboard::Key::Left:
            return movePlayer(Direction::Left);
        case sf::Keyboard::Key::D:
        case sf::Keyboard::Key::Right:
            return movePlayer(Direction::Right);
        case sf::Keyboard::Key::R:
            restart();
            return MoveResult::None;
        case sf::Keyboard::Key::Z:
            undo();
            return MoveResult::None;
        default:
            return MoveResult::None;
    }
}

void Level::restart() {
    loadLevelData(levelPaths[currentLevel]);
    player.syncVisualPosition();
    for (auto& box : boxes) {
        box.syncVisualPosition();
    }
}

int Level::getSteps() const {
    return steps;
}

bool Level::checkWin() const {
    for (auto target : targets) {
        bool isPlaced = false;
        for (auto& box : boxes) {
            if (box.getPosition().x == target.x && box.getPosition().y == target.y) {
                isPlaced = true;
            }
        }
        if (!isPlaced) {
            return false;
        }
    }
    return true;
}

void Level::next() {
    currentLevel++;
    if (currentLevel < levelPaths.size()) {
        loadLevelData(levelPaths[currentLevel]);
    } else {
        std::cout << "All of the levels are complete" << std::endl;
        currentLevel = 0;
        loadLevelData(levelPaths[currentLevel]);
    }
    player.syncVisualPosition();
    for (auto& box : boxes) {
        box.syncVisualPosition();
    }
}

void Level::initLevelList() {
    levelPaths.clear();
    currentLevel = 0;
    std::string path = "levels";
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto & entry : fs::directory_iterator(path)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    levelPaths.push_back(entry.path().string());
                }
            }
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Filesystem err: "<< err.what() << std::endl;
    }
    std::ranges::sort(levelPaths);
}

std::vector<Box>& Level::getBoxes(){
    return boxes;
}
Player& Level::getPlayer(){
    return player;
}
Map& Level::getMap(){
    return map;
}

void Level::undo() {
    if (moves.empty()) {
        return;
    }
    currState prevState = moves.top();
    moves.pop();
    player.setPosition({prevState.player.getPosition().x, prevState.player.getPosition().y});
    steps--;
    this->boxes = prevState.boxes;
    player.syncVisualPosition();
    for (auto& box : boxes) {
        box.syncVisualPosition();
    }
    changeBoxStates();
}

void Level::saveProgress(const int currentLevelIndex) {
    nlohmann::json saveData;

    if (std::ifstream inFile("save.json"); inFile.is_open()) {
        try {
            inFile >> saveData;
        } catch (const std::exception& e){
            std::cerr << "Warning: failed to parse save.json, creating new: " << e.what() << std::endl;
        }
    }

    saveData["level_index"] = currentLevelIndex;
    if (!saveData.contains("username")) {
        saveData["username"] = "Anonymous";
    }

    if (std::ofstream outFile("save.json"); outFile.is_open()) {
        outFile << saveData.dump(4);
    }
}

int Level::loadProgress() {
    if (std::ifstream inFile("save.json"); inFile.is_open()) {
        try {
            nlohmann::json saveData;
            inFile >> saveData;
            if (saveData.contains("level_index") && saveData["level_index"].is_number()) {
                return saveData["level_index"].get<int>();
            }
        } catch (std::exception& e) {
            std::cerr << "Failed to load progress: " << e.what() <<std::endl;
        }
    }
    return 1;
}

std::string Level::getSavePath() {
    int levelIndex = Level::loadProgress();

    std::ostringstream ss;
    ss << "levels/level" << std::setfill('0') << std::setw(2) << levelIndex << ".txt";
    return ss.str();
}


void Level::update(const float dt) {
    player.update(dt);
    for (auto& box: boxes) {
        box.update(dt);
    }
}

const std::vector<Box>& Level::getBoxes() const{
    return boxes;
}
const Player& Level::getPlayer() const{
    return player;
}
const Map& Level::getMap() const{
    return map;
}

bool Level::isLastLevel() const {
    if (currentLevel == levelPaths.size() - 1) {
        return true;
    }
    return false;
}

std::vector<std::string> Level::getLevelPaths() const {
    return levelPaths;
}

bool Level::isAnimating() const {
    if (player.isMoving()) return true;
    for (auto& box : boxes) {
        if (box.isMoving()) return true;
    }
    return false;
}

int Level::getCurrentLevelIndex() const {
    return currentLevel;
}

void Level::changeBoxStates(){
    for (auto& box : boxes) {
        box.setOffTarget();
        for (const auto& target : targets) {
            if (box.getPosition().x == target.x && box.getPosition().y == target.y) {
                box.setOnTarget();
            }
        }
    }
}

namespace fs = std::filesystem;

int Level::getLevelCount() {
    const fs::path dirPath = "./levels";
    int fileCount = 0;

    try {
        if (fs::exists(dirPath) && fs::is_directory(dirPath)) {

            for (const auto& entry : fs::directory_iterator(dirPath)) {
                if (entry.is_regular_file()) {
                    fileCount++;
                }
            }
        } else {
            std::cout << "Path does not exist or is not a directory." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return fileCount;
}

