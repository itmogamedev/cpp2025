#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "UIManager.h"

class Game {
public:
    Game();
    void run();

private:
    void initGame();
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleMouseClick(const sf::Vector2i& mousePos);

    sf::RenderWindow window;
    std::vector<sf::CircleShape> circles;
    UIManager ui;

    // Рандом
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> disX;
    std::uniform_real_distribution<> disY;

    int score;
    int radius;
    float timeLeft;
    bool gameActive;

    sf::Font font;

    sf::Clock clock;
};