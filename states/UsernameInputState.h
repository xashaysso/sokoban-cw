#pragma once

#include "../states/AppState.h"
#include <nlohmann/json.hpp>

#include "../graphics/UsernameInputRenderer.h"

class StateManager;

class UsernameInputState : public AppState{
public:
    UsernameInputState(StateManager &manager, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void update(float dt) override;

    static void saveUsername(std::string username);
    static std::string loadUsername();
private:
    StateManager& manager;
    UsernameInputRenderer renderer;
    std::string inputString;

    float cursorTimer = 0.f;
    bool showCursor = true;
    const size_t maxUsernameLength = 15;
};

