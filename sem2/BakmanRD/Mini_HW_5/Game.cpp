//
// Created by Bakman Roman on 25.05.2026.
//

#include "Game.h"
#include <algorithm>
#include <string>

Game::Game()
    : window(sf::VideoMode({800, 600}), "Space Shooter"),
      uiText(font),
      gameOverText(font) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
  }

  uiText.setCharacterSize(24);
  uiText.setFillColor(sf::Color::White);
  uiText.setPosition({10.f, 10.f});

  gameOverText.setCharacterSize(50);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setString("GAME OVER\nPress R to Restart");

  sf::FloatRect textRect = gameOverText.getLocalBounds();
  gameOverText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                          textRect.position.y + textRect.size.y / 2.0f});
  gameOverText.setPosition({800.f / 2.0f, 600.f / 2.0f});

  player.setPointCount(3);
  player.setPoint(0, {0.f, -20.f});
  player.setPoint(1, {-15.f, 20.f});
  player.setPoint(2, {15.f, 20.f});
  player.setFillColor(sf::Color::Cyan);

  resetGame();
}

void Game::resetGame() {
  player.setPosition({400.f, 550.f});
  playerSpeed = 400.f;
  lives = 3;
  score = 0;

  bullets.clear();
  asteroids.clear();

  baseReloadTime = 0.5f;
  timeSinceLastFire = baseReloadTime;

  asteroidSpawnTimer = 0.f;
  asteroidSpawnInterval = 1.0f;
  gameTime = 0.f;

  isGameOver = false;
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Time deltaTime = clock.restart();
    processEvents();
    if (!isGameOver) {
      update(deltaTime);
    }
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    else if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
      if (isGameOver && keyPress->code == sf::Keyboard::Key::R) {
        resetGame();
      }
    }
  }
}

void Game::update(sf::Time deltaTime) {
  float dt = deltaTime.asSeconds();
  gameTime += dt;
  timeSinceLastFire += dt;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    player.move({-playerSpeed * dt, 0.f});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    player.move({playerSpeed * dt, 0.f});
  }

  sf::Vector2f pos = player.getPosition();
  if (pos.x < 15.f) player.setPosition({15.f, pos.y});
  if (pos.x > 785.f) player.setPosition({785.f, pos.y});

  float currentReload = std::max(0.1f, baseReloadTime - (score * 0.01f));

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
      timeSinceLastFire >= currentReload) {
    Bullet b;
    b.shape.setSize({4.f, 15.f});
    b.shape.setFillColor(sf::Color::Yellow);
    b.shape.setPosition(
        {player.getPosition().x - 2.f, player.getPosition().y - 20.f});
    b.speed = 600.f;
    bullets.push_back(b);
    timeSinceLastFire = 0.f;
  }

  for (auto it = bullets.begin(); it != bullets.end();) {
    it->shape.move({0.f, -it->speed * dt});
    if (it->shape.getPosition().y < 0) {
      it = bullets.erase(it);
    } else {
      ++it;
    }
  }

  asteroidSpawnTimer += dt;
  if (asteroidSpawnTimer >= asteroidSpawnInterval) {
    Asteroid a;
    a.shape.setRadius(20.f);
    a.shape.setFillColor(sf::Color(150, 150, 150));
    a.shape.setOrigin({20.f, 20.f});

    float randomX = static_cast<float>(std::rand() % 760 + 20);
    a.shape.setPosition({randomX, -20.f});
    a.speed = 100.f + (gameTime * 5.f);

    asteroids.push_back(a);
    asteroidSpawnTimer = 0.f;
  }

  for (auto a_it = asteroids.begin(); a_it != asteroids.end();) {
    a_it->shape.move({0.f, a_it->speed * dt});
    bool asteroidDestroyed = false;

    if (a_it->shape.getGlobalBounds()
            .findIntersection(player.getGlobalBounds())
            .has_value()) {
      lives--;
      asteroidDestroyed = true;
      if (lives <= 0) {
        isGameOver = true;
      }
    }

    if (!asteroidDestroyed) {
      for (auto b_it = bullets.begin(); b_it != bullets.end();) {
        if (a_it->shape.getGlobalBounds()
                .findIntersection(b_it->shape.getGlobalBounds())
                .has_value()) {
          score++;
          asteroidDestroyed = true;
          bullets.erase(b_it);
          break;
        }
        ++b_it;
      }
    }

    if (asteroidDestroyed || a_it->shape.getPosition().y > 620.f) {
      a_it = asteroids.erase(a_it);
    } else {
      ++a_it;
    }
  }

  uiText.setString("Score: " + std::to_string(score) +
                   " | Lives: " + std::to_string(lives));
}

void Game::render() {
  window.clear(sf::Color::Black);

  if (isGameOver) {
    window.draw(gameOverText);
    sf::Text finalScore = uiText;
    finalScore.setPosition({340.f, 380.f});
    window.draw(finalScore);
  } else {
    window.draw(player);
    for (const auto& bullet : bullets) {
      window.draw(bullet.shape);
    }
    for (const auto& asteroid : asteroids) {
      window.draw(asteroid.shape);
    }
    window.draw(uiText);
  }

  window.display();
}
