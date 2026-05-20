#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Card.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::unique_ptr<Card>> cards;

    Card* firstCard;
    Card* secondCard;
    int moves;
    int pairsFound;
    int consecutiveMisses;
    bool isWaiting;
    sf::Clock delayClock;

    sf::Text movesText;
    sf::Text gameOverText;
    bool gameFinished;

    void initializeCards();
    void handleMouseClick(float mouseX, float mouseY);
    void checkMatch();
    void resetSelection();
    void shuffleRemainingCards();
    void drawUI();

public:
    Game();
    void run();
};