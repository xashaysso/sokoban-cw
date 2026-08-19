#include "StatsRenderer.h"

#include "StatsRenderer.h"
#include <iostream>

StatsRenderer::StatsRenderer()
    : titleText(font),
      userText(font),
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
    titleText.setString("PERSONAL RECORDS");

    userText.setCharacterSize(24);
    userText.setFillColor(sf::Color::Cyan);

    loadingText.setCharacterSize(26);
    loadingText.setFillColor(sf::Color::Cyan);
    loadingText.setString("Loading player records...");

    headerText.setCharacterSize(24);
    headerText.setFillColor(sf::Color(255, 215, 0));

    rowText.setCharacterSize(24);
    rowText.setFillColor(sf::Color::White);

    hintText.setCharacterSize(20);
    hintText.setFillColor(sf::Color(180, 180, 180));
    hintText.setString("Press ESC to return to Menu");

    tableBox.setSize({700.f, 440.f});
    tableBox.setFillColor(sf::Color(25, 25, 35, 235));
    tableBox.setOutlineColor(sf::Color(70, 70, 100));
    tableBox.setOutlineThickness(3.f);
    tableBox.setOrigin({350.f, 220.f});
    tableBox.setPosition({512.f, 400.f});

    overlay.setFillColor(sf::Color(0, 0, 0, 230));
}

void StatsRenderer::render(sf::RenderWindow& window, const std::string& username,
                           const std::vector<UserStatsResponse>& stats, bool isLoading, bool hasError) {

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    overlay.setSize({windowWidth, windowHeight});
    window.draw(overlay);

    auto tBounds = titleText.getLocalBounds();
    titleText.setOrigin({tBounds.position.x + tBounds.size.x / 2.f, tBounds.position.y + tBounds.size.y / 2.f});
    titleText.setPosition({512.f, 60.f});
    window.draw(titleText);

    userText.setString("Player: " + username);
    auto uBounds = userText.getLocalBounds();
    userText.setOrigin({uBounds.position.x + uBounds.size.x / 2.f, uBounds.position.y + uBounds.size.y / 2.f});
    userText.setPosition({512.f, 115.f});
    window.draw(userText);

    window.draw(tableBox);

    if (isLoading) {
        auto lBounds = loadingText.getLocalBounds();
        loadingText.setOrigin({lBounds.position.x + lBounds.size.x / 2.f, lBounds.position.y + lBounds.size.y / 2.f});
        loadingText.setPosition({512.f, 400.f});
        window.draw(loadingText);
    } else if (hasError) {
        rowText.setFillColor(sf::Color(255, 100, 100));
        rowText.setString("Could not load stats from server");
        auto rBounds = rowText.getLocalBounds();
        rowText.setOrigin({rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f});
        rowText.setPosition({512.f, 400.f});
        window.draw(rowText);
    } else {
        const float colLevelX = 220.f;
        const float colStepsX = 470.f;
        const float colTimeX  = 670.f;
        const float headerY   = 210.f;

        headerText.setString("LEVEL");
        headerText.setPosition({colLevelX, headerY});
        window.draw(headerText);

        headerText.setString("BEST STEPS");
        headerText.setPosition({colStepsX, headerY});
        window.draw(headerText);

        headerText.setString("BEST TIME");
        headerText.setPosition({colTimeX, headerY});
        window.draw(headerText);

        sf::RectangleShape divider({640.f, 2.f});
        divider.setFillColor(sf::Color(80, 80, 110));
        divider.setPosition({192.f, 250.f});
        window.draw(divider);

        float rowY = 265.f;
        for (size_t i = 0; i < stats.size() && i < 8; ++i) {
            const auto& entry = stats[i];

            rowText.setFillColor(sf::Color(255, 215, 0));
            rowText.setString("Level " + std::to_string(entry.level_id));
            rowText.setPosition({colLevelX, rowY});
            window.draw(rowText);

            rowText.setFillColor(sf::Color::White);
            rowText.setString(std::to_string(entry.steps));
            rowText.setPosition({colStepsX + 25.f, rowY});
            window.draw(rowText);

            int eMins = entry.time / 60;
            int eSecs = entry.time % 60;
            std::string timeFormatted = (eMins < 10 ? "0" : "") + std::to_string(eMins) + ":"
                                      + (eSecs < 10 ? "0" : "") + std::to_string(eSecs);
            rowText.setString(timeFormatted);
            rowText.setPosition({colTimeX + 15.f, rowY});
            window.draw(rowText);

            rowY += 40.f;
        }

        if (stats.empty()) {
            rowText.setFillColor(sf::Color(180, 180, 180));
            rowText.setString("You haven't completed any levels yet!");
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
}