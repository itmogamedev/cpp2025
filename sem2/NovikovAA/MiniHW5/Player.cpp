#include "Player.h"

Player::Player() {
  shape.setSize(sf::Vector2f(80.f, 30.f));
  shape.setFillColor(sf::Color::Cyan);

  shape.setPosition(sf::Vector2f(360.f, 540.f));

  speed = 400.f;
}

void Player::update(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    shape.move(sf::Vector2f(-speed * dt, 0.f));
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    shape.move(sf::Vector2f(speed * dt, 0.f));
  }

  if (shape.getPosition().x < 0)
    shape.setPosition(sf::Vector2f(0, shape.getPosition().y));

  if (shape.getPosition().x + shape.getSize().x > 800)
    shape.setPosition(
        sf::Vector2f(800 - shape.getSize().x, shape.getPosition().y));
}

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::Vector2f Player::getPosition() const { return shape.getPosition(); }

sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }
