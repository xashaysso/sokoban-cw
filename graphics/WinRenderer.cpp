#include "WinRenderer.h"
#include <iostream>

WinRenderer::WinRenderer()
    : titleText(font),
      currentStatsText(font),
      hintText(font),
      loadingText(font),
      headerText(font),
      rowText(font)
{
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    titleText.setCharacterSize(38);
    titleText.setFillColor(sf::Color::Yellow);

    currentStatsText.setCharacterSize(22);
    currentStatsText.setFillColor(sf::Color(100, 255, 100));

    loadingText.setCharacterSize(24);
    loadingText.setFillColor(sf::Color::Cyan);
    loadingText.setString("Loading leaderboard...");

    headerText.setCharacterSize(20);
    headerText.setFillColor(sf::Color(255, 215, 0));

    rowText.setCharacterSize(20);
    rowText.setFillColor(sf::Color::White);

    hintText.setCharacterSize(20);
    hintText.setFillColor(sf::Color(200, 200, 200));

    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    tableBox.setSize({620.f, 260.f});
    tableBox.setFillColor(sf::Color(30, 30, 40, 220));
    tableBox.setOutlineColor(sf::Color(70, 70, 90));
    tableBox.setOutlineThickness(2.f);
}

void WinRenderer::render(sf::RenderWindow &window, int steps, float time, bool isLastLevel,
                         const std::vector<LevelStatsResponse>& stats, bool isLoading, bool hasError) {
    sf::View gameView = window.getView();
    window.setView(window.getDefaultView());

    overlay.setSize(sf::Vector2f(window.getSize()));
    window.draw(overlay);

    const int mins = static_cast<int>(time) / 60;
    const int secs = static_cast<int>(time) % 60;
    const std::string timeStr = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);

    if (isLastLevel) {
        titleText.setString("ALL LEVELS COMPLETED!");
        hintText.setString("Press Enter to return to Menu...");
    } else if (hasError) {
        rowText.setFillColor(sf::Color(255, 100, 100));
        rowText.setString("Could not connect to server");
        auto rBounds = rowText.getLocalBounds();
        rowText.setOrigin({rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f});
        rowText.setPosition({512.f, 290.f});
        window.draw(rowText);
    } else {
        titleText.setString("LEVEL COMPLETED!");
        hintText.setString("Press ENTER for Next Level / ESC for Menu");
    }

    auto tBounds = titleText.getLocalBounds();
    titleText.setOrigin({tBounds.position.x + tBounds.size.x / 2.f, tBounds.position.y + tBounds.size.y / 2.f});
    titleText.setPosition({512.f, 80.f});
    window.draw(titleText);

    currentStatsText.setString("Your Run: " + std::to_string(steps) + " steps  |  Time: " + timeStr);
    auto cBounds = currentStatsText.getLocalBounds();
    currentStatsText.setOrigin({cBounds.position.x + cBounds.size.x / 2.f, cBounds.position.y + cBounds.size.y / 2.f});
    currentStatsText.setPosition({512.f, 130.f});
    window.draw(currentStatsText);

    tableBox.setPosition({202.f, 170.f});
    window.draw(tableBox);

    if (isLoading) {
        auto lBounds = loadingText.getLocalBounds();
        loadingText.setOrigin({lBounds.position.x + lBounds.size.x / 2.f, lBounds.position.y + lBounds.size.y / 2.f});
        loadingText.setPosition({512.f, 290.f});
        window.draw(loadingText);
    } else {
        const float colRankX   = 230.f;
        const float colNameX   = 290.f;
        const float colStepsX  = 560.f;
        const float colTimeX   = 680.f;
        const float headerY    = 185.f;

        headerText.setString("#");
        headerText.setPosition({colRankX, headerY});
        window.draw(headerText);

        headerText.setString("PLAYER");
        headerText.setPosition({colNameX, headerY});
        window.draw(headerText);

        headerText.setString("STEPS");
        headerText.setPosition({colStepsX, headerY});
        window.draw(headerText);

        headerText.setString("TIME");
        headerText.setPosition({colTimeX, headerY});
        window.draw(headerText);

        sf::RectangleShape divider({580.f, 1.f});
        divider.setFillColor(sf::Color(80, 80, 100));
        divider.setPosition({222.f, 215.f});
        window.draw(divider);

        float rowY = 225.f;
        const size_t maxRows = std::min(stats.size(), size_t(5));

        for (size_t i = 0; i < maxRows; ++i) {
            const auto& entry = stats[i];

            rowText.setFillColor(i == 0 ? sf::Color(255, 215, 0) : sf::Color::White);

            rowText.setString(std::to_string(i + 1));
            rowText.setPosition({colRankX, rowY});
            window.draw(rowText);

            std::string name = entry.username;
            if (name.length() > 14) {
                name = name.substr(0, 12) + "..";
            }
            rowText.setString(name);
            rowText.setPosition({colNameX, rowY});
            window.draw(rowText);

            rowText.setString(std::to_string(entry.steps));
            rowText.setPosition({colStepsX, rowY});
            window.draw(rowText);

            int eMins = entry.time / 60;
            int eSecs = entry.time % 60;
            std::string entryTime = (eMins < 10 ? "0" : "") + std::to_string(eMins) + ":"
                                  + (eSecs < 10 ? "0" : "") + std::to_string(eSecs);
            rowText.setString(entryTime);
            rowText.setPosition({colTimeX, rowY});
            window.draw(rowText);

            rowY += 36.f;
        }

        if (stats.empty()) {
            rowText.setFillColor(sf::Color(180, 180, 180));
            rowText.setString("No records yet for this level!");
            auto rBounds = rowText.getLocalBounds();
            rowText.setOrigin({rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f});
            rowText.setPosition({512.f, 290.f});
            window.draw(rowText);
        }
    }

    auto hBounds = hintText.getLocalBounds();
    hintText.setOrigin({hBounds.position.x + hBounds.size.x / 2.f, hBounds.position.y + hBounds.size.y / 2.f});
    hintText.setPosition({512.f, 465.f});
    window.draw(hintText);

    window.setView(gameView);
}