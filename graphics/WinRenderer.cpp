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

    titleText.setCharacterSize(44);
    titleText.setFillColor(sf::Color::Yellow);

    currentStatsText.setCharacterSize(26);
    currentStatsText.setFillColor(sf::Color(100, 255, 100));

    loadingText.setCharacterSize(28);
    loadingText.setFillColor(sf::Color::Cyan);
    loadingText.setString("Loading leaderboard...");

    headerText.setCharacterSize(24);
    headerText.setFillColor(sf::Color(255, 215, 0));

    rowText.setCharacterSize(24);
    rowText.setFillColor(sf::Color::White);

    hintText.setCharacterSize(22);
    hintText.setFillColor(sf::Color(200, 200, 200));

    overlay.setFillColor(sf::Color(0, 0, 0, 190));

    tableBox.setSize({760.f, 420.f});
    tableBox.setFillColor(sf::Color(25, 25, 35, 235));
    tableBox.setOutlineColor(sf::Color(70, 70, 100));
    tableBox.setOutlineThickness(3.f);
    tableBox.setOrigin({380.f, 210.f});
    tableBox.setPosition({512.f, 400.f});
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
        hintText.setString("Press ENTER to return to Menu");
    } else {
        titleText.setString("LEVEL COMPLETED!");
        hintText.setString("Press ENTER for Next Level / ESC for Menu");
    }

    auto tBounds = titleText.getLocalBounds();
    titleText.setOrigin({tBounds.position.x + tBounds.size.x / 2.f, tBounds.position.y + tBounds.size.y / 2.f});
    titleText.setPosition({512.f, 60.f});
    window.draw(titleText);

    currentStatsText.setString("Steps: " + std::to_string(steps) + " |  Time: " + timeStr);
    auto cBounds = currentStatsText.getLocalBounds();
    currentStatsText.setOrigin({cBounds.position.x + cBounds.size.x / 2.f, cBounds.position.y + cBounds.size.y / 2.f});
    currentStatsText.setPosition({512.f, 120.f});
    window.draw(currentStatsText);

    window.draw(tableBox);

    if (isLoading) {
        auto lBounds = loadingText.getLocalBounds();
        loadingText.setOrigin({lBounds.position.x + lBounds.size.x / 2.f, lBounds.position.y + lBounds.size.y / 2.f});
        loadingText.setPosition({512.f, 400.f});
        window.draw(loadingText);
    } else if (hasError) {
        rowText.setFillColor(sf::Color(255, 100, 100));
        rowText.setString("Could not connect to server");
        auto rBounds = rowText.getLocalBounds();
        rowText.setOrigin({rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f});
        rowText.setPosition({512.f, 400.f});
        window.draw(rowText);
    } else {
        const float colRankX   = 170.f;
        const float colNameX   = 240.f;
        const float colStepsX  = 570.f;
        const float colTimeX   = 720.f;
        const float headerY    = 210.f;

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

        sf::RectangleShape divider({700.f, 2.f});
        divider.setFillColor(sf::Color(80, 80, 110));
        divider.setPosition({162.f, 250.f});
        window.draw(divider);

        float rowY = 265.f;
        const size_t maxRows = std::min(stats.size(), size_t(8));

        for (size_t i = 0; i < maxRows; ++i) {
            const auto& entry = stats[i];

            if (i == 0)      rowText.setFillColor(sf::Color(255, 215, 0));
            else if (i == 1) rowText.setFillColor(sf::Color(215, 215, 225));
            else if (i == 2) rowText.setFillColor(sf::Color(205, 127, 50));
            else             rowText.setFillColor(sf::Color::White);

            rowText.setString(std::to_string(i + 1));
            rowText.setPosition({colRankX, rowY});
            window.draw(rowText);

            std::string name = entry.username;
            if (name.length() > 18) {
                name = name.substr(0, 16) + "..";
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

            rowY += 40.f;
        }

        if (stats.empty()) {
            rowText.setFillColor(sf::Color(180, 180, 180));
            rowText.setString("No records yet for this level!");
            auto rBounds = rowText.getLocalBounds();
            rowText.setOrigin({rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f});
            rowText.setPosition({512.f, 400.f});
            window.draw(rowText);
        }
    }

    auto hBounds = hintText.getLocalBounds();
    hintText.setOrigin({hBounds.position.x + hBounds.size.x / 2.f, hBounds.position.y + hBounds.size.y / 2.f});
    hintText.setPosition({512.f, 670.f});
    window.draw(hintText);

    window.setView(gameView);
}