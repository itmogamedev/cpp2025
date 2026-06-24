#include "game.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

#include "constants.h"

bool Game::load() {
  if (!loadTexture(player_texture, "assets/sprites/player.png")) {
    std::cerr << "Failed to load player sprite\n";
    return false;
  }

  for (int index = 0; index < int(alien_textures.size()); ++index) {
    std::string path = "assets/sprites/alien" + numberText(index + 1) + ".png";
    if (!loadTexture(alien_textures[index], path)) {
      std::cerr << "Failed to load " << path << '\n';
      return false;
    }
  }

  if (!loadFont(font, "assets/fonts/clacon2.ttf")) {
    std::cerr << "Failed to load assets/fonts/clacon2.ttf\n";
    return false;
  }

  player.setup(player_texture);
  makeStars();
  restart();
  return true;
}

int Game::run() {
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                          "Mini Homework 5: Space Shooter");
  window.setFramerateLimit(60);

  sf::Clock clock;
  while (window.isOpen()) {
    readEvents(window);
    float time = std::min(clock.restart().asSeconds(), 0.05f);
    update(time, true);
    draw(window);
  }
  return 0;
}

void Game::restart() {
  state = GameState::play;
  score = 0;
  lives = startLives;
  game_time = 0.0f;
  reload = 0.0f;
  shots.clear();
  asteroids.clear();
  player.reset();

  asteroids.reserve(asteroidCount);
  for (int index = 0; index < asteroidCount; ++index) {
    asteroids.insert(
        asteroids.end(),
        Asteroid(alien_textures[index % int(alien_textures.size())]));
    asteroids.back().respawn(random, asteroidSpeed(), false);
  }
}

void Game::readEvents(sf::RenderWindow& window) {
  while (std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (state == GameState::over && key->code == sf::Keyboard::Key::R) {
        restart();
      }
    }
  }
}

void Game::update(float time, bool read_keyboard_now) {
  if (state == GameState::over) {
    return;
  }

  game_time += time;
  reload = std::max(0.0f, reload - time);

  if (read_keyboard_now) {
    readKeyboard(time);
  }

  player.update(time);
  moveShots(time);
  moveAsteroids(time);
  checkHits();
  clearShots();
}

void Game::readKeyboard(float time) {
  float direction = 0.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    direction -= 1.0f;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    direction += 1.0f;
  }
  if (direction != 0.0f) {
    player.move(direction, time);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    shoot();
  }
}

void Game::moveShots(float time) {
  for (Projectile& shot : shots) {
    shot.update(time);
  }
}

void Game::moveAsteroids(float time) {
  for (Asteroid& asteroid : asteroids) {
    asteroid.update(time);
    if (asteroid.bounds().position.y > float(windowHeight)) {
      asteroid.respawn(random, asteroidSpeed(), true);
    }
  }
}

void Game::checkHits() {
  for (Projectile& shot : shots) {
    if (!shot.isActive()) {
      continue;
    }

    for (Asteroid& asteroid : asteroids) {
      if (shot.bounds().findIntersection(asteroid.bounds())) {
        shot.stop();
        ++score;
        asteroid.respawn(random, asteroidSpeed(), true);
        break;
      }
    }
  }

  if (!player.canBeHit()) {
    return;
  }

  for (Asteroid& asteroid : asteroids) {
    if (player.bounds().findIntersection(asteroid.bounds())) {
      --lives;
      asteroid.respawn(random, asteroidSpeed(), true);
      if (lives <= 0) {
        state = GameState::over;
      } else {
        player.blink();
      }
      break;
    }
  }
}

void Game::draw(sf::RenderWindow& window) const {
  window.clear(sf::Color(3, 4, 8));
  drawBackground(window);
  for (const Asteroid& asteroid : asteroids) {
    asteroid.draw(window);
  }
  for (const Projectile& shot : shots) {
    shot.draw(window);
  }
  player.draw(window);
  drawUi(window);
  window.display();
}

void Game::drawBackground(sf::RenderWindow& window) const {
  sf::RectangleShape star({2.0f, 2.0f});
  star.setFillColor(sf::Color(150, 150, 150));

  int shift = int(game_time * 18.0f) % int(windowHeight);
  for (sf::Vector2f point : stars) {
    point.y += float(shift);
    if (point.y > float(windowHeight)) {
      point.y -= float(windowHeight);
    }
    star.setPosition(point);
    window.draw(star);
  }
}

void Game::drawUi(sf::RenderWindow& window) const {
  std::string status =
      "SCORE: " + numberText(score) + "   LIVES: " + numberText(lives) +
      "   RELOAD: " + numberText(int(reloadTime() * 1000.0f)) + " MS";
  drawText(window, status, 22, {16.0f, 14.0f}, sf::Color::White);
  drawText(window, "A/D OR LEFT/RIGHT IS MOVE    SPACE IS FIRE", 16,
           {16.0f, 44.0f}, sf::Color(180, 220, 255));

  if (state == GameState::over) {
    sf::RectangleShape cover({float(windowWidth), float(windowHeight)});
    cover.setFillColor(sf::Color(0, 0, 0, 170));
    window.draw(cover);

    drawCenterText(window, "GAME OVER", 54, 245.0f, sf::Color(255, 60, 60));
    drawCenterText(window, "FINAL SCORE: " + numberText(score), 28, 320.0f,
                   sf::Color::White);
    drawCenterText(window, "PRESS R TO RESTART", 22, 370.0f,
                   sf::Color(160, 255, 160));
  }
}

void Game::drawText(sf::RenderWindow& window, const std::string& text,
                    unsigned int size, sf::Vector2f point,
                    sf::Color color) const {
  sf::Text shadow(font, text, size);
  shadow.setFillColor(sf::Color(0, 0, 0, 230));
  shadow.setPosition({point.x + 2.0f, point.y + 2.0f});
  window.draw(shadow);

  sf::Text visible(font, text, size);
  visible.setFillColor(color);
  visible.setPosition(point);
  window.draw(visible);
}

void Game::drawCenterText(sf::RenderWindow& window, const std::string& text,
                          unsigned int size, float y, sf::Color color) const {
  sf::Text visible(font, text, size);
  sf::FloatRect area = visible.getLocalBounds();
  visible.setOrigin({area.position.x + area.size.x / 2.0f,
                     area.position.y + area.size.y / 2.0f});
  visible.setPosition({float(windowWidth) / 2.0f, y});

  sf::Text shadow = visible;
  shadow.setFillColor(sf::Color(0, 0, 0, 230));
  shadow.move({3.0f, 3.0f});
  visible.setFillColor(color);

  window.draw(shadow);
  window.draw(visible);
}

void Game::shoot() {
  if (state == GameState::play && reload <= 0.0f) {
    shots.insert(shots.end(), Projectile(player.shotPoint()));
    reload = reloadTime();
  }
}

void Game::clearShots() {
  for (int index = 0; index < int(shots.size());) {
    if (!shots[index].isActive()) {
      shots.erase(shots.begin() + index);
    } else {
      ++index;
    }
  }
}

float Game::reloadTime() const {
  return std::max(minReload, startReload - float(score) * reloadStep);
}

float Game::asteroidSpeed() const { return 85.0f + game_time * 4.0f; }

void Game::makeStars() {
  stars.clear();
  for (int index = 0; index < 80; ++index) {
    stars.insert(stars.end(),
                 sf::Vector2f(random.randomFloat(0.0f, float(windowWidth)),
                              random.randomFloat(0.0f, float(windowHeight))));
  }
}

std::string Game::findAsset(const std::string& path) const {
  std::ifstream file(path);
  if (file.good()) {
    return path;
  }
  return "";
}

std::string Game::numberText(int number) const {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}
bool Game::loadTexture(sf::Texture& texture, const std::string& path) const {
  std::string file = findAsset(path);
  if (file.empty()) {
    return false;
  }
  try {
    texture = sf::Texture(file);
  } catch (...) {
    return false;
  }
  texture.setSmooth(false);
  return true;
}

bool Game::loadFont(sf::Font& target, const std::string& path) const {
  std::string file = findAsset(path);
  if (file.empty()) {
    return false;
  }
  try {
    target = sf::Font(file);
  } catch (...) {
    return false;
  }
  return true;
}
