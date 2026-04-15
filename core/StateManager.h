#pragma once

#include <vector>
#include <memory>

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
    private:
        std::vector<std::unique_ptr<AppState>> states;
};
