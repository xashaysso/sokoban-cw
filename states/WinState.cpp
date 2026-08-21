#include "WinState.h"

#include <iostream>
#include <utility>

#include "MenuState.h"
#include "UsernameInputState.h"

WinState::WinState(StateManager &manager, const int levelId, const int steps, const float time, const bool isLast, std::function<void()> onConfirm) : manager(
    manager), net(manager.getNetwork()), levelId(levelId), finalSteps(steps), finalTime(time), lastLevel(isLast), onConfirm(std::move(onConfirm)) {
    auto &audio = manager.getAudio();
    audio.loadSound("win", "audio/win.wav");
    audio.playSound("win", 60.0f);

    std::string username = UsernameInputState::loadUsername();
    if (username.empty()) username = "Anonymous";

    LevelStatsRequest req{username, steps, static_cast<int>(time)};

    auto alive = this->isAlive;

    net.sendLevelStats(levelId, req, [alive](bool ok) {
        if (!alive->load()) {
            return;
        }
        if (ok) {
            std::cout << "Stats sent. Fetching leaderboard..." << std::endl;
        }
    });
    net.getLevelStats(this->levelId, [this, alive](bool success, const std::vector<LevelStatsResponse> &stats) {
        if (!*alive) {
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

WinState::~WinState() {
    *isAlive = false;
}



void WinState::draw(sf::RenderWindow &window) {
    std::vector<LevelStatsResponse> currentStats;
    bool loading;
    bool error;
    {
        std::lock_guard<std::mutex> lock(dataMutex);
        currentStats = leaderboard;
        loading = isLoading;
        error = hasError;
    }
    renderer.render(window, finalSteps, finalTime, lastLevel, currentStats, loading, error);
}

void WinState::update(float dt) {}

void WinState::handleInput(sf::RenderWindow &window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                auto& m = manager;
                m.popState();
                onConfirm();
                return;
            }
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            std::cout << "Level completed" << std::endl;

            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                auto& m = manager;
                m.popState();
                onConfirm();
                return;
            }
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                manager.changeState(std::make_unique<MenuState>(manager, window));
                return;
            }
        }
    }
}


