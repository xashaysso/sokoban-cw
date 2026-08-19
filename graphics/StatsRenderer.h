#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../entities/Stats.h"

class StatsRenderer {
public:
    StatsRenderer();
    void render(sf::RenderWindow& window, const std::string& username,
                const std::vector<UserStatsResponse>& stats, bool isLoading, bool hasError);

private:
    sf::Font font;
    sf::RectangleShape tableBox;
    sf::Text titleText;
    sf::Text userText;
    sf::Text hintText;
    sf::Text loadingText;
    sf::Text headerText;
    sf::Text rowText;
    sf::RectangleShape overlay;
};