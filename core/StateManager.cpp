#include "StateManager.h"

#include <iostream>
#include <stack>

#include "../states/AppState.h"

AppState *StateManager::getCurrentState() const {
    if (states.empty()) {
        return nullptr;
    }
    return states.empty() ? nullptr : states.back().get();
}

void StateManager::pushState(std::unique_ptr<AppState> newState) {
    states.push_back(std::move(newState));
}

void StateManager::popState() {
    if (!states.empty()) {
        states.pop_back();
    }
}

void StateManager::changeState(std::unique_ptr<AppState> newState) {
    if (!states.empty()) {
        states.pop_back();
    }
    states.push_back(std::move(newState));
}

void StateManager::resetToState(std::unique_ptr<AppState> newState) {
    states.clear();
    states.push_back(std::move(newState));
}

void StateManager::draw(sf::RenderWindow& window) const {
    for (auto &state : states) {
        state->draw(window);
    }
}

void StateManager::startMusic(const std::string &path, float volume) {
    if (currentMusic) {
        fadingMusic = std::move(currentMusic);
    }
    currentMusic = std::make_unique<sf::Music>();
    if (currentMusic->openFromFile(path)) {
        currentMusic->setLooping(true);
        currentMusic->setVolume(volume);
        currentMusic->play();
        musicTargetVolume = volume;
    }
}

void StateManager::update(float dt) {
    if (fadingMusic) {
        float vol = fadingMusic->getVolume();
        vol -= fadeSpeed * dt;
        if (vol <= 0.0f) {
            fadingMusic->stop();
            fadingMusic.reset();
        } else {
            fadingMusic->setVolume(vol);
        }
    }
}






