#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Constants.h"

Game::Game()
    : window(sf::VideoMode({kWindowWidth, kWindowHeight}), kWindowTitle),
      font(),
      scoreText(font),
      livesText(font),
      gameOverText(font, "GAME OVER", kTextSizeGameOver),
      finalScoreText(font),
      score(0),
      asteroidSpawnTimer(0.0f),
      asteroidSpawnInterval(kInitialSpawnInterval),
      timeElapsed(0.0f),
      gameOver(false) {
  window.setFramerateLimit(kFramerateLimit);
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  if (!font.openFromFile("fonts/arialbd.ttf")) {
  }

  scoreText.setCharacterSize(kTextSizeScore);
  scoreText.setFillColor(kTextColor);
  scoreText.setPosition({kTextMargin, kScoreTextY});

  livesText.setCharacterSize(kTextSizeScore);
  livesText.setFillColor(kTextColor);
  livesText.setPosition({kTextMargin, kLivesTextY});

  gameOverText.setFillColor(kGameOverColor);
  sf::FloatRect goBounds = gameOverText.getLocalBounds();
  gameOverText.setOrigin({goBounds.size.x / 2.0f, goBounds.size.y / 2.0f});
  gameOverText.setPosition({kGameOverTextX, kGameOverTextY});

  finalScoreText.setCharacterSize(kTextSizeFinalScore);
  finalScoreText.setFillColor(kTextColor);

  player.setPosition({kPlayerStartX, kPlayerStartY});
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
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
    } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::Space && !gameOver) {
        if (player.canShoot()) {
          sf::Vector2f pos = player.getPosition();
          float bulletX = pos.x - kBulletWidth / 2.0f;
          float bulletY =
              pos.y - player.getBounds().size.y / 2.0f - kBulletHeight;
          bullets.emplace_back(bulletX, bulletY);
          player.resetCooldown();
        }
      }
    }
  }
}

void Game::update(float dt) {
  float dx = 0.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    dx -= kPlayerMoveSpeed * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    dx += kPlayerMoveSpeed * dt;
  }
  if (dx != 0.0f) {
    sf::Vector2f pos = player.getPosition();
    pos.x += dx;
    float halfWidth = player.getBounds().size.x / 2.0f;
    float windowWidth = static_cast<float>(window.getSize().x);
    pos.x = std::clamp(pos.x, halfWidth, windowWidth - halfWidth);
    player.setPosition(pos);
  }

  player.update(dt);

  for (auto& bullet : bullets) bullet.update(dt);
  for (auto& asteroid : asteroids) asteroid.update(dt);

  checkCollisions();

  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [this](const Bullet& b) {
                                 return b.isOffScreen(
                                     static_cast<float>(window.getSize().y));
                               }),
                bullets.end());
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [this](const Asteroid& a) {
                                   return a.isOffScreen(
                                       static_cast<float>(window.getSize().y));
                                 }),
                  asteroids.end());

  asteroidSpawnTimer -= dt;
  if (asteroidSpawnTimer <= 0.0f) {
    spawnAsteroid();
    asteroidSpawnInterval = std::max(
        kMinSpawnInterval,
        kInitialSpawnInterval - timeElapsed * kSpawnIntervalDecreaseRate);
    asteroidSpawnTimer = asteroidSpawnInterval;
  }

  timeElapsed += dt;
  player.setCooldown(computeCooldown(score));
}

void Game::render() {
  window.clear(kBackgroundColor);

  player.draw(window);
  for (const auto& bullet : bullets) bullet.draw(window);
  for (const auto& asteroid : asteroids) asteroid.draw(window);

  scoreText.setString("Score: " + std::to_string(score));
  livesText.setString("Lives: " + std::to_string(player.getLives()));
  window.draw(scoreText);
  window.draw(livesText);

  if (gameOver) {
    finalScoreText.setString("Final Score: " + std::to_string(score));
    sf::FloatRect fsBounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin({fsBounds.size.x / 2.0f, fsBounds.size.y / 2.0f});
    finalScoreText.setPosition({kFinalScoreTextX, kFinalScoreTextY});
    window.draw(gameOverText);
    window.draw(finalScoreText);
  }

  window.display();
}

void Game::spawnAsteroid() {
  float windowWidth = static_cast<float>(window.getSize().x);
  float radius = kAsteroidMinRadius +
                 static_cast<float>(std::rand() %
                                    static_cast<int>(kAsteroidMaxRadius -
                                                     kAsteroidMinRadius + 1));
  float x = radius + static_cast<float>(std::rand()) / RAND_MAX *
                         (windowWidth - 2 * radius);
  float y = -radius;
  float speed = kAsteroidBaseSpeed + timeElapsed * kAsteroidSpeedIncrease;
  asteroids.emplace_back(x, y, speed);
}

void Game::checkCollisions() {
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
    bool bulletHit = false;
    for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();) {
      if (bulletIt->getBounds()
              .findIntersection(asteroidIt->getBounds())
              .has_value()) {
        bulletHit = true;
        asteroidIt = asteroids.erase(asteroidIt);
        ++score;
        break;
      } else {
        ++asteroidIt;
      }
    }
    if (bulletHit) {
      bulletIt = bullets.erase(bulletIt);
    } else {
      ++bulletIt;
    }
  }

  for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();) {
    if (player.getBounds()
            .findIntersection(asteroidIt->getBounds())
            .has_value()) {
      player.takeDamage();
      if (!player.isAlive()) {
        gameOver = true;
      }
      asteroidIt = asteroids.erase(asteroidIt);
    } else {
      ++asteroidIt;
    }
  }
}

float Game::computeCooldown(int score) const {
  return std::max(kCooldownMin,
                  kPlayerInitialCooldown - score * kCooldownPerScore);
}
