#include "Player.h"

#include "Constants.h"

Player::Player()
    : lives(3),
      cooldownDuration(kPlayerInitialCooldown),
      cooldownTimer(0.0f),
      invulTimer(0.0f),
      invulnerable(false) {
  shape.setSize(sf::Vector2f(kPlayerWidth, kPlayerHeight));
  shape.setFillColor(kPlayerColor);
  shape.setOrigin(shape.getSize() / 2.0f);
}

void Player::update(float dt) {
  if (cooldownTimer > 0.0f) {
    cooldownTimer -= dt;
  }
  if (invulnerable) {
    invulTimer -= dt;
    if (invulTimer <= 0.0f) {
      invulnerable = false;
    }
  }
}

void Player::draw(sf::RenderWindow& window) const { window.draw(shape); }

void Player::setPosition(const sf::Vector2f& position) {
  shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const { return shape.getPosition(); }

sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }

bool Player::canShoot() const { return cooldownTimer <= 0.0f; }

void Player::resetCooldown() { cooldownTimer = cooldownDuration; }

void Player::setCooldown(float cooldown) { cooldownDuration = cooldown; }

void Player::takeDamage() {
  if (!invulnerable) {
    --lives;
    invulnerable = true;
    invulTimer = kPlayerInvulDuration;
  }
}

bool Player::isAlive() const { return lives > 0; }

int Player::getLives() const { return lives; }

bool Player::isInvulnerable() const { return invulnerable; }
