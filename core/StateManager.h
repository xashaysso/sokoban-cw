#pragma once

#include <vector>
#include <memory>

#include "SFML/Audio/Music.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class AppState;

class StateManager {
    public:
        void pushState(std::unique_ptr<AppState> newState);
        void popState();
        AppState* getCurrentState() const;
        void changeState(std::unique_ptr<AppState> newState);
        void draw(sf::RenderWindow& window) const;
        void resetToState(std::unique_ptr<AppState> newState);
        void startMusic(const std::string& path, float volume);
        void update(float dt);
    private:
        std::vector<std::unique_ptr<AppState>> states;

    // music control

        std::unique_ptr<sf::Music> currentMusic;
        std::unique_ptr<sf::Music> fadingMusic;
        float fadeSpeed = 50.f;
        float musicTargetVolume = 20.f;

};
