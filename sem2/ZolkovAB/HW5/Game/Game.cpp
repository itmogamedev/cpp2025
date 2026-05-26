#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>

Game::Game()
    : window(sf::VideoMode(sf::Vector2u(800, 600)),
             "Space Shooter - ISU 504643"),
      uiText(font),  
      gameOverText(font),
      finalScoreText(font) {
  window.setFramerateLimit(60);
  score = 0;
  lives = 3;
  asteroidSpeed = 2.0f;
  reloadTime = 0.5f;
  isGameOver = false;

  initUI();
}

void Game::initUI() {
  if (!font.openFromFile("ARIAL.TTF")) {
    std::cerr << "ОШИБКА: Не удалось загрузить шрифт ARIAL.TTF!" << std::endl;
    std::cerr << "Положите файл шрифта в папку с проектом." << std::endl;
  }

  uiText.setFont(font);
  uiText.setCharacterSize(24);
  uiText.setFillColor(sf::Color::White);
  uiText.setPosition(sf::Vector2f(10.f, 10.f));

  gameOverText.setFont(font);
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setString("GAME OVER");
  gameOverText.setPosition(sf::Vector2f(220.f, 200.f));

  finalScoreText.setFont(font);
  finalScoreText.setCharacterSize(30);
  finalScoreText.setFillColor(sf::Color::Yellow);
  finalScoreText.setPosition(sf::Vector2f(260.f, 280.f));
}

void Game::pollEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }
}

void Game::updateEntities() {
  player.update();

  // Стрельба
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
      bulletTimer.getElapsedTime().asSeconds() >= reloadTime) {
    bullets.push_back(
        Bullet(player.getPosition().x + 22.5f, player.getPosition().y));
    bulletTimer.restart();
  }

  if (asteroidTimer.getElapsedTime().asSeconds() >= 1.0f) {
    float randomX = static_cast<float>(rand() % 760);
    asteroids.push_back(Asteroid(randomX, asteroidSpeed));
    asteroidTimer.restart();

    asteroidSpeed += 0.05f;
    if (reloadTime > 0.15f) reloadTime -= 0.01f;
  }

  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i].update();
    if (bullets[i].getPositionY() < 0) {
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }

  for (size_t i = 0; i < asteroids.size(); i++) {
    asteroids[i].update();
    if (asteroids[i].getPositionY() > 600) {
      asteroids.erase(asteroids.begin() + i);
      i--;
    }
  }
}

void Game::updateCollisions() {
  for (size_t i = 0; i < asteroids.size(); i++) {
    if (asteroids[i]
            .getBounds()
            .findIntersection(player.getBounds())
            .has_value()) {
      asteroids.erase(asteroids.begin() + i);
      lives--;
      if (lives <= 0) {
        isGameOver = true;
        finalScoreText.setString("Final Score: " + std::to_string(score));
      }
      break;
    }

    for (size_t j = 0; j < bullets.size(); j++) {
      if (asteroids.size() > i &&
          bullets[j]
              .getBounds()
              .findIntersection(asteroids[i].getBounds())
              .has_value()) {
        asteroids.erase(asteroids.begin() + i);
        bullets.erase(bullets.begin() + j);
        score++;
        break;
      }
    }
  }
}

void Game::render() {
  window.clear();

  if (!isGameOver) {
    player.render(window);
    for (auto& bullet : bullets) bullet.render(window);
    for (auto& asteroid : asteroids) asteroid.render(window);

    window.draw(uiText);
  } else {
    window.draw(gameOverText);
    window.draw(finalScoreText);
  }

  window.display();
}

void Game::run() {
  while (window.isOpen()) {
    pollEvents();

    if (!isGameOver) {
      updateEntities();
      updateCollisions();

      uiText.setString("Score: " + std::to_string(score) +
                       "\nHP: " + std::to_string(lives));
    }

    render();
  }
}