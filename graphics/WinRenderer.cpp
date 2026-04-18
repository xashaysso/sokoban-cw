#include "WinRenderer.h"

#include <iostream>

WinRenderer::WinRenderer() : titleText(font), statsText(font), hintText(font) {
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    titleText.setFont(font);
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Yellow);

    statsText.setFont(font);
    statsText.setCharacterSize(30);
    statsText.setFillColor(sf::Color::White);

    hintText.setFont(font);
    hintText.setCharacterSize(20);
    hintText.setFillColor(sf::Color(200, 200, 200));

    overlay.setFillColor(sf::Color(0, 0, 0, 150));
}

void WinRenderer::render(sf::RenderWindow &window, int steps, float time, bool isLastLevel) {
    overlay.setSize(sf::Vector2f(window.getSize()));
    window.draw(overlay);

    const int mins = static_cast<int>(time) / 60;
    const int secs = static_cast<int>(time) % 60;
    const std::string timeStr = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);

    if (isLastLevel) {
        titleText.setString("ALL LEVELS COMPLETED!");
        hintText.setString("Press Enter to return to Menu...");
    } else {
        titleText.setString("LEVEL COMPLETED!");
        hintText.setString("Press ENTER for Next Level / ESC for Menu");
    }

    statsText.setString("Steps: " + std::to_string(steps) + "| Time: " + timeStr);

    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    auto centerText = [&](sf::Text& text, float yOffset) {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        text.setPosition({center.x, center.y + yOffset});
    };

    centerText(titleText, -50.f);
    centerText(statsText, 20.f);
    centerText(hintText, 100.f);

    window.draw(titleText);
    window.draw(statsText);
    window.draw(hintText);
}

