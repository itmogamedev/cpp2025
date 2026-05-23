#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "game.h"

Game::Game()
    : window(sf::VideoMode({WINDOW_W, WINDOW_H}), "CPP game",
             sf::Style::Titlebar | sf::Style::Close),
      player({WINDOW_W / 2.f, WINDOW_H - 60.f}),
      ui(font) {
  std::srand((unsigned)std::time(nullptr));
  window.setFramerateLimit(60);

  if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
    font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
  }
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    dt = std::min(dt, 0.05f);  // cap delta to avoid recuring deaths

    processEvents();
    if (state == GameState::Playing) update(dt);
    render();
  }
}

void Game::processEvents() {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (state == GameState::GameOver) {
      if (event->is<sf::Event::KeyPressed>()) {
        auto code = event->getIf<sf::Event::KeyPressed>()->code;

        if (code == sf::Keyboard::Key::R) {
          reset();
        }
      }
    }
  }
}

void Game::update(float dt) {
  player.handleInput(dt);

  if (player.tryShoot(dt, score)) {
    bullets.emplace_back(player.getPosition() + sf::Vector2f{0.f, -30.f});
  }

  spawnTimer += dt;
  spawnInterval = std::max(ASTEROID_SPAWN_MIN,
                           ASTEROID_SPAWN_BASE - (float)(score / 8) * 0.08f);
  if (spawnTimer >= spawnInterval) {
    spawnTimer = 0.f;
    spawnAsteroid();
  }

  for (auto& b : bullets) b.update(dt);

  float astSpeed =
      ASTEROID_BASE_SPEED + (float)(score / 10) * ASTEROID_SPEED_STEP;
  for (auto& a : asteroids) {
    a.speed = astSpeed;
    a.update(dt);
  }

  for (auto& b : bullets) {
    if (!b.active) continue;
    for (auto& a : asteroids) {
      if (!a.active) continue;
      if (a.shape.getGlobalBounds().contains(b.shape.getPosition())) {
        b.active = false;
        a.active = false;
        ++score;
      }
    }
  }

  for (auto& a : asteroids) {
    if (!a.active) continue;
    if (player.getBounds().findIntersection(a.shape.getGlobalBounds())) {
      a.active = false;
      --player.lives;
      if (player.lives <= 0) state = GameState::GameOver;
      break;
    }
  }

  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](const Bullet& b) { return !b.active; }),
                bullets.end());
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](const Asteroid& b) { return !b.active; }),
                  asteroids.end());
}

void Game::render() {
  window.clear(sf::Color::Black);

  if (state == GameState::Playing) {
    for (auto& a : asteroids) {
      window.draw(a.shape);
    }
    for (auto& b : bullets) {
      window.draw(b.shape);
    }
    window.draw(player.getShape());
    ui.draw(window, score, player.lives);
  } else {
    ui.drawGameOver(window, score);
  }

  window.display();
}

void Game::spawnAsteroid() {
  float x = 30.f + (float)(std::rand() % (WINDOW_W - 60));
  float spd = ASTEROID_BASE_SPEED + (float)(score / 10) * ASTEROID_SPEED_STEP;
  asteroids.emplace_back(x, spd);
}

void Game::reset() {
  player = Player({WINDOW_W / 2.f, WINDOW_H - 60.f});
  bullets.clear();
  asteroids.clear();
  score = 0;
  spawnTimer = 0.f;
  state = GameState::Playing;
}