#pragma once

#include "../core/Level.h"
#include "../graphics/Renderer.h"
#include "../states/AppState.h"

class StateManager;

class PlayState: public AppState{
    public:
        PlayState(StateManager &manager);

        void handleInput(sf::RenderWindow& window) override;
        void draw(sf::RenderWindow& window) override;
    private:
        StateManager& manager;
        Level level;
        Renderer renderer;
        const unsigned int tileSize = 64u;
};

