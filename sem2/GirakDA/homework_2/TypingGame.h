#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class TypingGame {
public:
    TypingGame();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title_text;
    sf::Text char_text;
    sf::Text score_text;
    sf::Text timer_text;
    sf::Text game_over_text;
    sf::Text restart_text;

    char current_char;
    int score;
    float time_left;
    bool game_active;

    void setupText();
    void generateRandomChar();
    void handleInput(char input);
    void updateText();
    void resetGame();
};