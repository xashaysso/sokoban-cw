#include "MenuState.h"

#include <fstream>

#include "ControlsState.h"
#include "LevelSwitcherState.h"
#include "PlayState.h"
#include "StatsState.h"

MenuState::MenuState(StateManager& manager, sf::RenderWindow& window): manager(manager), selectedOption(0) {
    options = {"NEW GAME", "CONTINUE", "STATS", "CONTROLS", "EXIT"};

    window.setSize({1024u, 768u});
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (desktop.size.x - 1024) / 2,
        (desktop.size.y - 768) / 2
    ));
    sf::View view(sf::FloatRect({0.f, 0.f}, {1024.f, 768.f}));
    window.setView(view);

    hasSave = hasSaveProgress();

    auto& audio = manager.getAudio();
    audio.loadSound("click", "audio/click.wav");
    audio.loadSound("select", "audio/select.wav");
    audio.startMusic("audio/menu.ogg", 20.0f);
}

bool MenuState::hasSaveProgress() {
    if (!std::filesystem::exists("save.json")) {
        return false;
    }

    try {
        std::ifstream inFile("save.json");
        if (!inFile.is_open()) {
            return false;
        }

        nlohmann::json saveData;
        inFile >> saveData;

        return saveData.contains("level_index") &&
               saveData["level_index"].is_number_integer() &&
               saveData["level_index"].get<int>() > 1;
    } catch (...) {
        return false;
    }
}

void MenuState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseMoved->position, window.getDefaultView());
            int hoveredIdx = renderer.getHoveredOption(mousePos, options, window.getSize());
            if (hoveredIdx != -1) {
                if (hoveredIdx != 1 || hasSave) { // 1 = CONTINUE
                    selectedOption = hoveredIdx;
                }
            }
        }

        if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseBtn->position, window.getDefaultView());
                int clickedIdx = renderer.getHoveredOption(mousePos, options, window.getSize());
                if (clickedIdx != -1) {
                    selectedOption = clickedIdx;
                    executeOption(window);
                    return;
                }
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            auto& audio = manager.getAudio();
            switch (keyPressed->code) {
                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Up:
                    if (selectedOption == 0) {
                        selectedOption = options.size() - 1;
                    } else {
                        selectedOption--;
                        if (selectedOption == 1 && !hasSave) {
                            selectedOption--;
                        }
                    }
                    audio.playSound("click", 15.f);
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    if (selectedOption == options.size() - 1) {
                        selectedOption = 0;
                    } else {
                        selectedOption++;
                        if (selectedOption == 1 && !hasSave) {
                            selectedOption++;
                        }
                    }
                    audio.playSound("click", 15.f);
                    break;
                case sf::Keyboard::Key::Enter:
                    executeOption(window);
                    return;
            }
        }
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    renderer.render(window, options, selectedOption, hasSave);
}

void MenuState::update(float dt) {}

void MenuState::executeOption(sf::RenderWindow &window) {
    auto& audio = manager.getAudio();
    auto& m = manager;
    audio.playSound("select", 15.f);
    switch (selectedOption) {
        case 0:
            m.changeState(std::make_unique<PlayState>(m, window, "levels/level01.txt"));
            break;
        case 1: {
            if (hasSave) {
                m.pushState(std::make_unique<LevelSwitcherState>(m));
            }
            break;
        }
        case 2: {
            m.pushState(std::make_unique<StatsState>(m));
            break;
        }
        case 3:
            m.pushState(std::make_unique<ControlsState>(m));
            break;
        default:
            window.close();
            break;
    }
}