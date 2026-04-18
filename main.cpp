#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/StateManager.h"
#include "states/MenuState.h"
#include "states/PlayState.h"


int main()
{
    try {
        StateManager manager;
        sf::Clock clock;

        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Evanescence", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);

        manager.pushState(std::make_unique<MenuState>(manager, window));

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
