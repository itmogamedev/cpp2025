#include <algorithm>

#include "game.h"

Player::Player(sf::Vector2f pos) {
  shape.setPointCount(3);
  shape.setPoint(0, {0.f, -28.f});
  shape.setPoint(1, {12.f, 22.f});
  shape.setPoint(2, {-12.f, 22.f});

  shape.setFillColor(sf::Color::Blue);
  shape.setPosition(pos);

  lives = MAX_LIVES;
  reloadTimer = 0;
}

void Player::handleInput(float dt) {
  float dx = 0.f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    dx -= PLAYER_SPEED * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    dx += PLAYER_SPEED * dt;
  }

  shape.move({dx, 0.f});

  auto pos = shape.getPosition();
  pos.x = std::clamp(pos.x, 28.f, (float)WINDOW_W - 28.f);
  shape.setPosition(pos);
}

bool Player::tryShoot(float dt, int score) {
  reloadTimer -= dt;
  if (reloadTimer > 0.f) return false;
  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) return false;

  float reload = RELOAD_BASE - (float)(score / 5) * RELOAD_STEP;
  reload = std::max(reload, RELOAD_MIN);
  reloadTimer = reload;
  return true;
}

const sf::ConvexShape& Player::getShape() { return shape; }

sf::Vector2f Player::getPosition() { return shape.getPosition(); }

sf::FloatRect Player::getBounds() { return shape.getGlobalBounds(); }
