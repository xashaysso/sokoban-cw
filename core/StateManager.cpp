#include "StateManager.h"

#include "../states/AppState.h"

AppState *StateManager::getCurrentState() {
    if (states.empty()) {
        return nullptr;
    }
    return states.top().get();
}

void StateManager::pushState(std::unique_ptr<AppState> newState) {
    states.push(std::move(newState));
}

void StateManager::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void StateManager::changeState(std::unique_ptr<AppState> newState) {
    if (!states.empty()) {
        states.pop();
    }
    states.push(std::move(newState));
}


