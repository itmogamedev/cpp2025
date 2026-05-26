#include "Game.h"
#include "constants.h"
#include <ctime>
#include <cstdlib>

Game::Game()
    : m_screenWidth(SCREEN_WIDTH_F), m_screenHeight(SCREEN_HEIGHT_F),
      m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Shooter", sf::Style::Close),
      m_model(SCREEN_WIDTH_F, SCREEN_HEIGHT_F),
      m_view(SCREEN_WIDTH_F, SCREEN_HEIGHT_F)
{
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    srand(static_cast<unsigned int>(time(0)));
    m_view.loadResources();
}

void Game::run()
{
    sf::Clock clock;
    while (m_window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        handleInput(deltaTime);
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                m_window.close();

        }
    }
}

void Game::handleInput(float deltaTime)
{
    if (m_model.getState() != GameState::Playing)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_model.moveShipLeft(deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_model.moveShipRight(deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_model.shoot();
    }
}

void Game::update(float deltaTime)
{
    m_model.update(deltaTime);
}

void Game::render()
{
    m_view.render(m_window, m_model);
}
