#pragma once

#include "../core/Level.h"
#include "../graphics/LevelRenderer.h"
#include "../states/AppState.h"

class StateManager;

class PlayState: public AppState{
    public:
        PlayState(StateManager &manager, sf::RenderWindow& window, std::string path);

        void handleInput(sf::RenderWindow& window) override;
        void draw(sf::RenderWindow& window) override;
        void update(float dt) override;
        void initWindow(sf::RenderWindow& window) const;

    private:
        StateManager& manager;
        Level level;
        LevelRenderer renderer;
        sf::RenderWindow& renderWindow;
        const unsigned int tileSize;

        sf::Clock levelClock;
        bool winStatePushed;
};

