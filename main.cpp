#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/StateManager.h"
#include "states/MenuState.h"
#include "states/PlayState.h"
#include "network/NetworkManager.h"
#include "entities/Stats.h"
#include "states/UsernameInputState.h"


int main()
{
    try {
        StateManager manager;
        sf::Clock clock;

        sf::RenderWindow window(sf::VideoMode({1024u, 768u}), "Sokoban", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);

        std::string username = UsernameInputState::loadUsername();
        if (username.empty()) {
            manager.pushState(std::make_unique<UsernameInputState>(manager, window));
        } else {
            manager.pushState(std::make_unique<MenuState>(manager, window));
        }

        NetworkManager net("http://localhost:8080");

        // test
        LevelStatsRequest req{"Player1", 42, 120};
        net.sendLevelStats(1, req, [&net](bool ok) {
            if (ok) {
                std::cout << "POST OK. Fetching stats..." << std::endl;

                net.getLevelStats(1, [](bool success, const auto& stats) {
                    if (success) {
                        std::cout << "GET OK. Received data from Go!" << std::endl;
                    }
                });
            }
        });

        while (window.isOpen()) {
            const float dt = clock.restart().asSeconds();

            if (auto* current = manager.getCurrentState()) {
                current->handleInput(window);
            }

            manager.update(dt);

            window.clear(sf::Color(30, 30, 30));
            manager.draw(window);
            window.display();
        }
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        return -1;
    }
    return 0;
}
