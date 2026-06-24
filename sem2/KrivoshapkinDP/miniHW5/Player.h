#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
 public:
  Player();

  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  void setPosition(const sf::Vector2f& position);
  sf::Vector2f getPosition() const;
  sf::FloatRect getBounds() const;

  bool canShoot() const;
  void resetCooldown();
  void setCooldown(float cooldown);

  void takeDamage();
  bool isAlive() const;
  int getLives() const;
  bool isInvulnerable() const;

 private:
  sf::RectangleShape shape;
  int lives;
  float cooldownDuration;
  float cooldownTimer;
  float invulTimer;
  bool invulnerable;
};

#endif
