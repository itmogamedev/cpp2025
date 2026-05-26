#pragma once
#include <SFML/Graphics.hpp>
#include "GameModel.h"

class GameView
{
public:
    GameView(float screenWidth, float screenHeight);

    void loadResources();
    void render(sf::RenderWindow& window, GameModel& model);

private:
    void drawBackground(sf::RenderWindow& window);
    void drawHUD(sf::RenderWindow& window, GameModel& model);
    void drawGameOver(sf::RenderWindow& window, GameModel& model);

    float m_screenWidth;
    float m_screenHeight;

    sf::Texture m_shipTexture;
    sf::Texture m_asteroidTexture;
    sf::Texture m_backgroundTexture;

    sf::Sprite m_backgroundSprite;

    sf::Font m_font;
};
