#include "Game.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Circle.h"
#include "Constants.h"

Game::Game()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
               "OSU at home - MiniHW2"),
      m_score(0),
      m_remainingTime(GAME_DURATION),
      m_isGameOver(false) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  if (m_font.openFromFile("resources/font.ttf")) {
    m_scoreText.emplace(m_font);
    m_scoreText->setCharacterSize(SCORE_TEXT_SIZE);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition({10.f, 10.f});
    m_scoreText->setString("Score: 0");

    m_timerText.emplace(m_font);
    m_timerText->setCharacterSize(TIMER_TEXT_SIZE);
    m_timerText->setFillColor(sf::Color::White);
    m_timerText->setPosition({10.f, 50.f});
    m_timerText->setString("Time: " + std::to_string(GAME_DURATION));

    m_gameOverText.emplace(m_font);
    m_gameOverText->setCharacterSize(GAME_OVER_TEXT_SIZE);
    m_gameOverText->setFillColor(sf::Color::Red);
    m_gameOverText->setPosition({200.f, 250.f});
  }

  for (int i = 0; i < CIRCLE_COUNT; ++i) {
    float x =
        CIRCLE_RADIUS +
        static_cast<float>(
            rand() % (WINDOW_WIDTH - 2 * static_cast<int>(CIRCLE_RADIUS)));
    float y =
        CIRCLE_RADIUS +
        static_cast<float>(
            rand() % (WINDOW_HEIGHT - 2 * static_cast<int>(CIRCLE_RADIUS)));
    m_circles.push_back(
        std::make_unique<Circle>(sf::Vector2f(x, y), CIRCLE_RADIUS));
  }
}

Game::~Game() = default;

void Game::run() {
  while (m_window.isOpen()) {
    float deltaTime = m_clock.restart().asSeconds();
    if (deltaTime > 0.033f) deltaTime = 0.033f;

    processEvents();
    if (!m_isGameOver) {
      update(deltaTime);
    }
    render();
  }
}

void Game::processEvents() {
  while (auto event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window.close();
    } else if (!m_isGameOver && event->is<sf::Event::MouseButtonPressed>()) {
      auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
      if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
        sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x),
                              static_cast<float>(mouseEvent->position.y));
        bool hit = false;
        for (auto& circle : m_circles) {
          if (circle->contains(mousePos)) {
            hit = true;
            m_score += SCORE_PER_HIT;
            if (m_scoreText.has_value()) {
              m_scoreText->setString("Score: " + std::to_string(m_score));
            }
            respawnCircle(circle.get());
            break;
          }
        }
        if (!hit) {
          m_remainingTime -= MISS_PENALTY;
          if (m_remainingTime < 0.f) m_remainingTime = 0.f;
        }
      }
    }
  }
}

void Game::update(float deltaTime) {
  if (m_remainingTime > 0.f) {
    m_remainingTime -= deltaTime;
    if (m_remainingTime <= 0.f) {
      m_remainingTime = 0.f;
      endGame();
    }
  }

  if (m_timerText.has_value()) {
    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "Time: %.1f", m_remainingTime);
    m_timerText->setString(buffer);
  }

  for (auto& circle : m_circles) {
    circle->update(deltaTime, static_cast<float>(WINDOW_WIDTH),
                   static_cast<float>(WINDOW_HEIGHT));
  }
}

void Game::render() {
  m_window.clear(sf::Color::Black);
  for (auto& circle : m_circles) {
    circle->draw(m_window);
  }
  if (m_scoreText.has_value()) m_window.draw(*m_scoreText);
  if (m_timerText.has_value()) m_window.draw(*m_timerText);
  if (m_isGameOver && m_gameOverText.has_value())
    m_window.draw(*m_gameOverText);
  m_window.display();
}

void Game::respawnCircle(Circle* circle) {
  float x = CIRCLE_RADIUS +
            static_cast<float>(
                rand() % (WINDOW_WIDTH - 2 * static_cast<int>(CIRCLE_RADIUS)));
  float y = CIRCLE_RADIUS +
            static_cast<float>(
                rand() % (WINDOW_HEIGHT - 2 * static_cast<int>(CIRCLE_RADIUS)));
  circle->setPosition(sf::Vector2f(x, y));
  circle->resetVelocity();
}

void Game::endGame() {
  if (m_isGameOver) return;
  m_isGameOver = true;
  m_circles.clear();
  if (m_gameOverText.has_value()) {
    m_gameOverText->setString("GAME OVER\nFinal score: " +
                              std::to_string(m_score));
  }
}
