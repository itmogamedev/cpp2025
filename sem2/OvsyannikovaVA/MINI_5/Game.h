#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Card.h"

class Game
{
private:
    sf::RenderWindow window;

    std::vector<Card> cards;

    sf::Font font;

    Card* firstCard = nullptr;
    Card* secondCard = nullptr;

    sf::Text winText;
    sf::Text movesText;

    bool gameWon = false;

    int moves = 0;
    int score = 0;
    int mistakesInRow = 0;

    bool waiting = false;

    void initCards();

    void processEvents();
    void update();
    void render();

    void checkPair();
    void shuffleCards();

public:
    Game();

    void run();
};