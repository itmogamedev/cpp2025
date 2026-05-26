#pragma once
#include <SFML/Graphics.hpp>
#include "GameModel.h"
#include "GameView.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();

    float m_screenWidth;
    float m_screenHeight;

    sf::RenderWindow m_window;
    GameModel m_model;
    GameView m_view;
};
