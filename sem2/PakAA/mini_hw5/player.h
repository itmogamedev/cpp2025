#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
 public:
  Player(float window_width, float window_height);

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;

  void moveLeft(float delta_time);
  void moveRight(float delta_time);

  // Возвращает true, если перезарядка завершилась и можно стрелять.
  bool canShoot() const;
  // Регистрирует выстрел и запускает таймер перезарядки.
  void shoot();
  // Перезарядка ускоряется с ростом счёта (по ТЗ).
  void updateReloadTime(int score);

  sf::FloatRect getBounds() const;
  sf::Vector2f getPosition() const;

  int getLives() const;
  void loseLife();
  bool isAlive() const;

  // Краткая i-frames неуязвимость после получения урона,
  // чтобы один астероид не отъел сразу все жизни.
  bool isInvulnerable() const;

 private:
  sf::Sprite sprite;
  float window_width;
  float speed;
  float reload_timer;
  float current_reload_time;
  float invulnerability_timer;
  int lives;
};

#endif  // SPACE_SHOOTER_PLAYER_H
