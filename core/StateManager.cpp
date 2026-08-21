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
    pendingAction = PendingAction::Push;
    pendingState = std::move(newState);
}

void StateManager::popState() {
    pendingAction = PendingAction::Pop;
}

void StateManager::changeState(std::unique_ptr<AppState> newState) {
    pendingAction = PendingAction::Change;
    pendingState = std::move(newState);
}

void StateManager::resetToState(std::unique_ptr<AppState> newState) {
    pendingAction = PendingAction::Reset;
    pendingState = std::move(newState);
}

void StateManager::processPendingChanges() {
    if (pendingAction == PendingAction::None) {
        return;
    }

    switch (pendingAction) {
        case PendingAction::Push:
            if (pendingState) {
                states.push_back(std::move(pendingState));
            }
            break;
        case PendingAction::Pop:
            if (!states.empty()) {
                states.pop_back();
            }
            break;
        case PendingAction::Change:
            if (pendingState) {
                if (!states.empty()) {
                    states.pop_back();
                }
                states.push_back(std::move(pendingState));
            }
            break;
        case PendingAction::Reset:
            if (pendingState) {
                states.clear();
                states.push_back(std::move(pendingState));
            }
            break;
        default:
            break;
    }
    pendingAction = PendingAction::None;
    pendingState = nullptr;
}


void StateManager::draw(sf::RenderWindow& window) const {
    for (auto &state : states) {
        state->draw(window);
    }
}

AudioManager &StateManager::getAudio() {
    return audioManager;
}

NetworkManager &StateManager::getNetwork() {
    return networkManager;
}

void StateManager::update(const float dt) {
    audioManager.update(dt);
    if (!states.empty()) {
        states.back()->update(dt);
    }
}








