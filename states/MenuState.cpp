#include "MenuState.h"

#include "PlayState.h"

MenuState::MenuState(StateManager& manager, sf::RenderWindow& window): manager(manager), selectedOption(0) {
    options = {"START", "EXIT"};
    window.setSize({800u, 600u});
    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);

    auto& audio = manager.getAudio();
    audio.startMusic("audio/menu.ogg", 20.0f);
}

void MenuState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::W) {
                if (selectedOption == 0) {
                    selectedOption = options.size() - 1;
                } else {
                    selectedOption--;
                }
            }
            if (keyPressed->code == sf::Keyboard::Key::S) {
                if (selectedOption == options.size() - 1) {
                    selectedOption = 0;
                } else {
                    selectedOption++;
                }
            }
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                if (selectedOption == 0) {
                    auto& m = manager;
                    m.changeState(std::make_unique<PlayState>(m, window));
                    return;
                }
                window.close();
            }
        }
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    renderer.render(window, options, selectedOption);
}



