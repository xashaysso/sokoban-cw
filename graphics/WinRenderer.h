#pragma once
#include "../entities/Stats.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"


class WinRenderer {
    public:
        WinRenderer();
        void render(sf::RenderWindow &window, int steps, float time, bool isLastLevel, const std::vector<LevelStatsResponse>& stats, bool isLoading, bool hasError);
    private:
        sf::Font font;
        sf::RectangleShape overlay;
        sf::RectangleShape tableBox;
        sf::Text titleText;
        sf::Text currentStatsText;
        sf::Text hintText;
        sf::Text loadingText;
        sf::Text headerText;
        sf::Text rowText;
};
