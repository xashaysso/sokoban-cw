#include "UsernameInputRenderer.h"
#include <iostream>

UsernameInputRenderer::UsernameInputRenderer()
    : m_promptText(m_font),
      m_inputText(m_font),
      m_hintText(m_font)
{
    if (!m_font.openFromFile("fonts/font.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    m_promptText.setString("ENTER YOUR NICKNAME");
    m_promptText.setCharacterSize(44);
    m_promptText.setFillColor(sf::Color::White);
    auto pBounds = m_promptText.getLocalBounds();
    m_promptText.setOrigin({pBounds.position.x + pBounds.size.x / 2.f, pBounds.position.y + pBounds.size.y / 2.f});
    m_promptText.setPosition({512.f, 230.f});

    m_inputBox.setSize({520.f, 74.f});
    m_inputBox.setFillColor(sf::Color(35, 35, 45));
    m_inputBox.setOutlineColor(sf::Color(100, 149, 237));
    m_inputBox.setOutlineThickness(3.f);
    m_inputBox.setOrigin({260.f, 37.f});
    m_inputBox.setPosition({512.f, 350.f});

    m_inputText.setCharacterSize(38);
    m_inputText.setFillColor(sf::Color(255, 215, 0));

    m_hintText.setString("Press ENTER to confirm");
    m_hintText.setCharacterSize(22);
    m_hintText.setFillColor(sf::Color(170, 170, 170));
    auto hBounds = m_hintText.getLocalBounds();
    m_hintText.setOrigin({hBounds.position.x + hBounds.size.x / 2.f, hBounds.position.y + hBounds.size.y / 2.f});
    m_hintText.setPosition({512.f, 440.f});
}

void UsernameInputRenderer::render(sf::RenderWindow& window, const std::string& currentInput, bool showCursor) {
    window.draw(m_promptText);
    window.draw(m_inputBox);

    m_inputText.setString(currentInput + (showCursor ? "|" : ""));
    auto tBounds = m_inputText.getLocalBounds();
    m_inputText.setOrigin({tBounds.position.x + tBounds.size.x / 2.f, tBounds.position.y + tBounds.size.y / 2.f});
    m_inputText.setPosition({512.f, 348.f});
    window.draw(m_inputText);

    window.draw(m_hintText);
}