#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/StateManager.h"
#include "states/PlayState.h"


int main()
{
    try {
        StateManager manager;

        manager.pushState(std::make_unique<PlayState>(manager));

        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Evanescence", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);

        while (window.isOpen()) {
            AppState* current = manager.getCurrentState();
            if (current) {
                current->handleInput(window);
                current->draw(window);
                window.display();
            } else {
                window.close();
            }
        }
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        return -1;
    }
    return 0;
}
