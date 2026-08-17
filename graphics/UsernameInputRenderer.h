#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class UsernameInputRenderer {
public:
    UsernameInputRenderer();

    void render(sf::RenderWindow &window, const std::string& currentInput, bool showCursor);
private:
    sf::Font m_font;
    sf::Text m_promptText;
    sf::Text m_inputText;
    sf::Text m_hintText;
    sf::RectangleShape m_inputBox;
};
