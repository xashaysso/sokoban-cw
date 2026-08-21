#pragma once

#include <vector>
#include <memory>

#include "AudioManager.h"
#include "../network/NetworkManager.h"
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

        void processPendingChanges();

        AudioManager& getAudio();
        NetworkManager& getNetwork();
        void update(float dt);
    private:
        std::vector<std::unique_ptr<AppState>> states;
        AudioManager audioManager;
        NetworkManager networkManager{"http://127.0.0.1:8080"};

        enum class PendingAction { None, Push, Pop, Change, Reset };
        PendingAction pendingAction = PendingAction::None;
        std::unique_ptr<AppState> pendingState = nullptr;
};
