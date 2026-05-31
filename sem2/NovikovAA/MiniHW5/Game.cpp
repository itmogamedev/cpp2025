#include "Game.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>

Game::Game() : window(sf::VideoMode({800u, 600u}), "Space Shooter") {
  score = 0;
  lives = 3;

  gameOver = false;

  asteroidSpeed = 150.f;

  if (!font.openFromFile("assets/supermario3dworld.otf")) {
    std::cout << "FONT ERROR\n";
  }

  scoreText.emplace(font);
  livesText.emplace(font);
  gameOverText.emplace(font);

  scoreText->setCharacterSize(24);
  scoreText->setPosition(sf::Vector2f(10.f, 10.f));

  livesText->setCharacterSize(24);
  livesText->setPosition(sf::Vector2f(10.f, 40.f));

  gameOverText->setCharacterSize(40);
  gameOverText->setFillColor(sf::Color::Red);
  gameOverText->setPosition(sf::Vector2f(170.f, 250.f));
}

void Game::run() {
  while (window.isOpen()) {
    float dt = deltaClock.restart().asSeconds();

    processEvents();

    if (!gameOver) {
      update(dt);
    }

    render();
  }
}

void Game::processEvents() {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (!gameOver && event->is<sf::Event::KeyPressed>()) {
      auto keyEvent = event->getIf<sf::Event::KeyPressed>();

      if (keyEvent && keyEvent->code == sf::Keyboard::Key::Space) {
        if (shootClock.getElapsedTime().asSeconds() >= getShootCooldown()) {
          shoot();
          shootClock.restart();
        }
      }
    }
  }
}

void Game::update(float dt) {
  player.update(dt);

  asteroidSpeed += dt * 2.f;

  if (asteroidClock.getElapsedTime().asSeconds() >= 1.f) {
    spawnAsteroid();
    asteroidClock.restart();
  }

  for (auto& bullet : bullets) {
    bullet.update(dt);
  }

  for (auto& asteroid : asteroids) {
    asteroid.update(dt);
  }

  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](Bullet& b) { return b.getY() < -20.f; }),
                bullets.end());

  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](Asteroid& a) { return a.getY() > 620.f; }),
                  asteroids.end());

  bool collision = false;

  for (size_t i = 0; i < bullets.size() && !collision; ++i) {
    for (size_t j = 0; j < asteroids.size(); ++j) {
      if (bullets[i].getBounds().findIntersection(asteroids[j].getBounds())) {
        bullets.erase(bullets.begin() + i);

        asteroids.erase(asteroids.begin() + j);

        score++;

        collision = true;

        break;
      }
    }
  }

  for (size_t i = 0; i < asteroids.size(); ++i) {
    if (player.getBounds().findIntersection(asteroids[i].getBounds())) {
      asteroids.erase(asteroids.begin() + i);

      lives--;

      break;
    }
  }

  if (lives <= 0) {
    gameOver = true;

    std::stringstream ss;

    ss << "GAME OVER\n";
    ss << "Score: " << score;

    gameOverText->setString(ss.str());
  }

  scoreText->setString(sf::String("Score: " + std::to_string(score)));

  livesText->setString(sf::String("Lives: " + std::to_string(lives)));
}

void Game::render() {
  window.clear(sf::Color::Black);

  player.draw(window);

  for (auto& bullet : bullets) {
    bullet.draw(window);
  }

  for (auto& asteroid : asteroids) {
    asteroid.draw(window);
  }

  window.draw(*scoreText);
  window.draw(*livesText);

  if (gameOver) {
    window.draw(*gameOverText);
  }

  window.display();
}

void Game::shoot() {
  sf::Vector2f pos = player.getPosition();

  bullets.emplace_back(pos.x + 37.f, pos.y);
}

void Game::spawnAsteroid() {
  float x = static_cast<float>(std::rand() % 740);

  asteroids.emplace_back(x, asteroidSpeed);
}

float Game::getShootCooldown() {
  float cooldown = 0.6f - static_cast<float>(score) * 0.01f;

  if (cooldown < 0.15f) {
    cooldown = 0.15f;
  }

  return cooldown;
}
