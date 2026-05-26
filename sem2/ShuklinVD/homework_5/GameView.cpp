#include "GameView.h"
#include "constants.h"
#include <string>

GameView::GameView(float screenWidth, float screenHeight)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
}

void GameView::loadResources()
{
    m_shipTexture.loadFromFile("assets/ship.png");
    m_asteroidTexture.loadFromFile("assets/asteroid.png");
    m_backgroundTexture.loadFromFile("assets/background.png");
    m_font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    m_backgroundSprite.setTexture(m_backgroundTexture);
    sf::Vector2u bgSize = m_backgroundTexture.getSize();
    if (bgSize.x > 0 && bgSize.y > 0)
    {
        float scaleX = m_screenWidth / static_cast<float>(bgSize.x);
        float scaleY = m_screenHeight / static_cast<float>(bgSize.y);
        m_backgroundSprite.setScale(scaleX, scaleY);
    }
}

void GameView::render(sf::RenderWindow& window, GameModel& model)
{
    window.clear(sf::Color(BG_R, BG_G, BG_B));

    drawBackground(window);

    const std::vector<Bullet>& bullets = model.getBullets();
    for (size_t i = 0; i < bullets.size(); i++)
    {
        const Bullet& bullet = bullets[i];
        sf::RectangleShape rect(sf::Vector2f(bullet.getWidth(), bullet.getHeight()));
        rect.setPosition(bullet.getX(), bullet.getY());
        rect.setFillColor(sf::Color(BULLET_COLOR_R, BULLET_COLOR_G, BULLET_COLOR_B));
        window.draw(rect);
    }

    const std::vector<Asteroid>& asteroids = model.getAsteroids();
    for (size_t i = 0; i < asteroids.size(); i++)
    {
        Asteroid asteroid = asteroids[i];
        asteroid.setSprite(m_asteroidTexture);
        window.draw(asteroid.getSprite());
    }

    if (model.getState() == GameState::Playing)
    {
        Ship ship = model.getShip();
        ship.setSprite(m_shipTexture);
        window.draw(ship.getSprite());
    }

    drawHUD(window, model);

    if (model.getState() == GameState::GameOver)
        drawGameOver(window, model);

    window.display();
}

void GameView::drawBackground(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
}

void GameView::drawHUD(sf::RenderWindow& window, GameModel& model)
{
    sf::Text scoreText;
    scoreText.setFont(m_font);
    scoreText.setString("Score: " + std::to_string(model.getScore()));
    scoreText.setCharacterSize(HUD_TEXT_SIZE);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(HUD_SCORE_X, HUD_Y);
    window.draw(scoreText);

    sf::Text livesText;
    livesText.setFont(m_font);
    livesText.setString("Lives: " + std::to_string(model.getLives()));
    livesText.setCharacterSize(HUD_TEXT_SIZE);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(m_screenWidth - HUD_LIVES_OFFSET_X, HUD_Y);
    window.draw(livesText);
}

void GameView::drawGameOver(sf::RenderWindow& window, GameModel& model)
{
    sf::RectangleShape overlay(sf::Vector2f(m_screenWidth, m_screenHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, OVERLAY_ALPHA));
    window.draw(overlay);

    sf::Text gameOverText;
    gameOverText.setFont(m_font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(GAMEOVER_TEXT_SIZE);
    gameOverText.setFillColor(sf::Color(GAMEOVER_COLOR_R, GAMEOVER_COLOR_G, GAMEOVER_COLOR_B));
    sf::FloatRect goBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(goBounds.width / 2.f, goBounds.height / 2.f);
    gameOverText.setPosition(m_screenWidth / 2.f, m_screenHeight / 2.f - GAMEOVER_Y_OFFSET);
    window.draw(gameOverText);

    sf::Text finalScore;
    finalScore.setFont(m_font);
    finalScore.setString("Final Score: " + std::to_string(model.getScore()));
    finalScore.setCharacterSize(FINAL_SCORE_TEXT_SIZE);
    finalScore.setFillColor(sf::Color::White);
    sf::FloatRect fsBounds = finalScore.getLocalBounds();
    finalScore.setOrigin(fsBounds.width / 2.f, fsBounds.height / 2.f);
    finalScore.setPosition(m_screenWidth / 2.f, m_screenHeight / 2.f + FINAL_SCORE_Y_OFFSET);
    window.draw(finalScore);

}
