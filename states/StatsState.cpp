#include "StatsState.h"

#include "UsernameInputState.h"
#include "../core/StateManager.h"

StatsState::StatsState(StateManager &manager): manager(manager), net(manager.getNetwork()) {
    std::string username = UsernameInputState::loadUsername();
    if (username.empty()) {
        this->hasError = true;
        this->isLoading = false;
        return;
    }

    auto alive = this->isAlive;

    net.getUserStats(username, [this, alive](bool success, const std::vector<UserStatsResponse> &stats) {
        if (!alive->load()) {
            return;
        }
        std::lock_guard<std::mutex> lock(this->dataMutex);
        if (success) {
            this->leaderboard = stats;
            this->hasError = false;
        } else {
            this->hasError = true;
        }
        this->isLoading = false;
    });
}

void StatsState::draw(sf::RenderWindow &window) {
    std::vector<UserStatsResponse> currentStats;
    bool loading;
    bool error;
    {
        std::lock_guard<std::mutex> lock(this->dataMutex);
        currentStats = leaderboard;
        loading = isLoading;
        error = hasError;
    }

    const std::string username = UsernameInputState::loadUsername();
    renderer.render(window, username, currentStats, loading, error);
}

void StatsState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape || keyPressed->code == sf::Keyboard::Key::Enter) {
                manager.popState();
                return;
            }
        }
    }
}

void StatsState::update(float dt) {}


