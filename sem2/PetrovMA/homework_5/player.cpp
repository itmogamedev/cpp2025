#include "player.h"

#include <cmath>

Player::Player() { reset(sf::Vector2f(900.f, 600.f)); }

void Player::reset(const sf::Vector2f &windowSize) {
  stats.health = 3;
  stats.score = 0;
  stats.render.setSize(sf::Vector2f(50., 40.));
  stats.render.setFillColor(sf::Color(0, 0, 255));

  stats.render.setPosition({(windowSize.x - 50.f) / 2.f, windowSize.y - 40.f - 20.f});
}

void Player::tick(std::shared_ptr<sf::RenderWindow> rend, double_t dt) {
  bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
  bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

  auto pos = stats.render.getPosition();
  float speed = 400.f;

  if (left) {
    pos.x -= speed * dt;
  }
  if (right) {
    pos.x += speed * dt;
  }

  float min_x = 0.f;
  float max_x = static_cast<float>(rend->getSize().x) - stats.render.getSize().x;
  if (pos.x < min_x)
    pos.x = min_x;
  if (pos.x > max_x)
    pos.x = max_x;

  stats.render.setPosition(pos);
  rend->draw(stats.render);
}
