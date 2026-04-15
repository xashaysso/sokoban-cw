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

void StateManager::draw(sf::RenderWindow& window) const {
    for (auto &state : states) {
        state->draw(window);
    }
}

void StateManager::resetToState(std::unique_ptr<AppState> newState) {
    states.clear();
    states.push_back(std::move(newState));
}




