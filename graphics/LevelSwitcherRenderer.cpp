#include "LevelSwitcherRenderer.h"
#include <iostream>

LevelSwitcherRenderer::LevelSwitcherRenderer()
    : titleText(font),
      cardText(font),
      hintText(font)
{
    if (!font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    titleText.setCharacterSize(44);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setString("SELECT LEVEL");

    cardText.setCharacterSize(34);
    cardText.setStyle(sf::Text::Style::Bold);

    hintText.setCharacterSize(20);
    hintText.setFillColor(sf::Color(180, 180, 180));
    hintText.setString("ARROWS / WASD: Move  |  ENTER: Play  |  ESC: Back");

    cardBox.setSize({110.f, 110.f});
    cardBox.setOrigin({55.f, 55.f});

    overlay.setFillColor(sf::Color(0, 0, 0));
}

void LevelSwitcherRenderer::render(sf::RenderWindow &window, int totalLevels, int unlockedLevel, int selectedIndex) {

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    overlay.setSize({windowWidth, windowHeight});
    window.draw(overlay);

    auto tBounds = titleText.getLocalBounds();
    titleText.setOrigin({tBounds.position.x + tBounds.size.x / 2.f, tBounds.position.y + tBounds.size.y / 2.f});
    titleText.setPosition({512.f, 90.f});
    window.draw(titleText);

    const int cols = 5;
    const float startX = 232.f;
    const float startY = 270.f;
    const float gapX = 140.f;
    const float gapY = 150.f;

    for (int i = 0; i < totalLevels; ++i) {
        int col = i % cols;
        int row = i / cols;

        float posX = startX + col * gapX;
        float posY = startY + row * gapY;

        cardBox.setPosition({posX, posY});

        bool isUnlocked = (i + 1 <= unlockedLevel);
        bool isSelected = (i == selectedIndex);

        if (isSelected) {
            cardBox.setFillColor(isUnlocked ? sf::Color(60, 100, 160) : sf::Color(60, 40, 40));
            cardBox.setOutlineColor(sf::Color::Yellow);
            cardBox.setOutlineThickness(4.f);
        } else {
            cardBox.setFillColor(isUnlocked ? sf::Color(35, 40, 55) : sf::Color(20, 20, 25));
            cardBox.setOutlineColor(isUnlocked ? sf::Color(80, 90, 120) : sf::Color(50, 50, 60));
            cardBox.setOutlineThickness(2.f);
        }
        window.draw(cardBox);

        if (isUnlocked) {
            cardText.setString(std::to_string(i + 1));
            cardText.setFillColor(isSelected ? sf::Color::Yellow : sf::Color::White);
        } else {
            cardText.setString("X");
            cardText.setFillColor(sf::Color(100, 100, 100));
        }

        auto cBounds = cardText.getLocalBounds();
        cardText.setOrigin({cBounds.position.x + cBounds.size.x / 2.f, cBounds.position.y + cBounds.size.y / 2.f});
        cardText.setPosition({posX, posY});
        window.draw(cardText);
    }

    auto hBounds = hintText.getLocalBounds();
    hintText.setOrigin({hBounds.position.x + hBounds.size.x / 2.f, hBounds.position.y + hBounds.size.y / 2.f});
    hintText.setPosition({512.f, 660.f});
    window.draw(hintText);
}