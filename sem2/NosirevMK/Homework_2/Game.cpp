#include "Game.h"

#include <cstdlib>
#include <ctime>

Game::Game()
    : m_window(sf::VideoMode({800, 600}),
               "OSU Home Edition - 5 Moving Circles"),
      m_gameActive(true),
      m_mousePressed(false) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  m_window.setFramerateLimit(60);

  spawnCircles();
  m_ui.init();
}

void Game::spawnCircles() {
  float radius = 30.f;

  for (int i = 0; i < 5; ++i) {
    float posX =
        radius + static_cast<float>(std::rand()) /
                     (static_cast<float>(RAND_MAX) / (800.f - 2.f * radius));
    float posY =
        radius + static_cast<float>(std::rand()) /
                     (static_cast<float>(RAND_MAX) / (600.f - 2.f * radius));

    float velX = -300.f + static_cast<float>(std::rand()) /
                              (static_cast<float>(RAND_MAX) / 600.f);
    float velY = -300.f + static_cast<float>(std::rand()) /
                              (static_cast<float>(RAND_MAX) / 600.f);

    if (std::abs(velX) < 50.f) velX = (velX > 0.f) ? 120.f : -120.f;
    if (std::abs(velY) < 50.f) velY = (velY > 0.f) ? 120.f : -120.f;

    sf::Color randomColor = generateRandomColor();

    m_circles.emplace_back(radius, sf::Vector2f(posX, posY),
                           sf::Vector2f(velX, velY), randomColor);
  }
}

sf::Color Game::generateRandomColor() {
  static const std::vector<sf::Color> brightColors = {
      sf::Color::Red,           sf::Color(255, 100, 0),
      sf::Color::Yellow,        sf::Color(0, 255, 0),
      sf::Color(0, 255, 255),   sf::Color(100, 100, 255),
      sf::Color(255, 0, 255),   sf::Color(255, 100, 150),
      sf::Color(150, 255, 100), sf::Color(255, 200, 100)};

  int index = std::rand() % brightColors.size();
  return brightColors[index];
}

void Game::run() {
  while (m_window.isOpen()) {
    float deltaTime = m_clock.restart().asSeconds();
    if (deltaTime > 0.1f) deltaTime = 0.1f;

    processEvents();
    update(deltaTime);
    render();
  }
}

void Game::processEvents() {
  while (const std::optional<sf::Event> event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window.close();
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::R) {
        restart();
      }
      if (keyPressed->code == sf::Keyboard::Key::Q) {
        m_window.close();
      }
    }
  }
}

void Game::update(float deltaTime) {
  m_ui.update(m_score.getValue(), m_timer.getRemainingTime());

  if (m_gameActive && m_timer.getRemainingTime() > 0.f) {
    for (auto& circle : m_circles) {
      circle.update(deltaTime, m_window.getSize());
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!m_mousePressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        bool hitSomething = false;

        for (auto& circle : m_circles) {
          if (circle.isClicked(mousePos)) {
            m_score.increment();
            circle.teleportToRandomPosition(m_window.getSize());
            hitSomething = true;
            break;
          }
        }

        if (!hitSomething) {
          m_timer.reduce(3.f);
        }
        m_mousePressed = true;
      }
    } else {
      m_mousePressed = false;
    }

    m_timer.update(deltaTime);

    if (m_timer.getRemainingTime() <= 0.f) {
      m_timer.setZero();
      m_gameActive = false;
    }
  }
}

void Game::render() {
  m_window.clear(sf::Color::Black);

  if (m_gameActive && m_timer.getRemainingTime() > 0.f) {
    for (auto& circle : m_circles) {
      circle.draw(m_window);
    }

    m_ui.draw(m_window);
  } else {
    m_ui.showGameOver(m_window, m_score.getValue());
  }

  m_window.display();
}

void Game::restart() {
  m_score.reset();
  m_timer.reset();
  m_gameActive = true;

  m_circles.clear();
  spawnCircles();
}
