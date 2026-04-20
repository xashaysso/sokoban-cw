#include "MenuState.h"

#include <fstream>

#include "PlayState.h"

MenuState::MenuState(StateManager& manager, sf::RenderWindow& window): manager(manager), selectedOption(0) {
    options = {"NEW GAME", "CONTINUE", "EXIT"};
    window.setSize({800u, 600u});
    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);

    hasSave = std::filesystem::exists("save.txt");

    auto& audio = manager.getAudio();
    audio.loadSound("click", "audio/click.wav");
    audio.loadSound("select", "audio/select.wav");
    audio.startMusic("audio/menu.ogg", 20.0f);
}

void MenuState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            auto& audio = manager.getAudio();
            if (keyPressed->code == sf::Keyboard::Key::W) {
                if (selectedOption == 0) {
                    selectedOption = options.size() - 1;
                } else {
                    selectedOption--;
                    if (selectedOption == 1 && !hasSave) {
                        selectedOption--;
                    }
                }
                audio.playSound("click", 15.f);
            }
            if (keyPressed->code == sf::Keyboard::Key::S) {
                if (selectedOption == options.size() - 1) {
                    selectedOption = 0;
                } else {
                    selectedOption++;
                    if (selectedOption == 1 && !hasSave) {
                        selectedOption++;
                    }
                }
                audio.playSound("click", 15.f);
            }
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                auto& m = manager;
                audio.playSound("select", 15.f);
                switch (selectedOption) {
                    case 0:
                        m.changeState(std::make_unique<PlayState>(m, window, "levels/level01.txt"));
                        break;
                    case 1: {
                        std::ifstream saveFile("save.txt");
                        std::string levelPath = "levels/level01.txt";

                        if (saveFile.is_open()) {
                            int levelIndex;
                            if (saveFile >> levelIndex) {
                                std::ostringstream ss;
                                ss << "levels/level" << std::setfill('0') << std::setw(2) << levelIndex << ".txt";
                                levelPath = ss.str();
                            }
                            saveFile.close();
                        }
                        m.changeState(std::make_unique<PlayState>(m, window, levelPath));
                        break;
                    }
                    default:
                        window.close();
                        break;
                }
            }
        }
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    renderer.render(window, options, selectedOption, hasSave);
}

void MenuState::update(float dt) {}




