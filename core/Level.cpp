#include "Level.h"

#include <fstream>

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
            }
            if (map.getTile(x, y) == Tile::Player) {
                player.setPosition({x, y});
                player.syncVisualPosition();
                map.setTile(x, y, Tile::Empty);
            }
            if (map.getTile(x, y) == Tile::Target) {
                targets.emplace_back(x, y);
            }
        }
    }
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

MoveResult Level::handleInput(const sf::Keyboard::Key key, sf::RenderWindow& window) {
    switch (key) {
        case sf::Keyboard::Key::W: return movePlayer(Direction::Up);
        case sf::Keyboard::Key::S: return movePlayer(Direction::Down);
        case sf::Keyboard::Key::A: return movePlayer(Direction::Left);
        case sf::Keyboard::Key::D: return movePlayer(Direction::Right);
        case sf::Keyboard::Key::R:
            restart();
            return MoveResult::None;
        case sf::Keyboard::Key::Z: undo();
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
    saveProgress(currentLevel+1); // index + 1 = Level number
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
}

void Level::saveProgress(const int currentLevelIndex) {
    if (std::ofstream saveFile("save.txt"); saveFile.is_open()) {
        saveFile << currentLevelIndex;
        saveFile.close();
    }
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
